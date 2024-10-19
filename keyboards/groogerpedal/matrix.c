#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "analog.h"

// These are defined in the schematic diagram here: https://store-usa.arduino.cc/products/arduino-leonardo-with-headers
// The value to use in QMK is the relevant PXX value without the 'P'
#define LEONARDO_A0 F7
#define LEONARDO_A1 F6
#define LEONARDO_A2 F5
#define LEONARDO_A3 F4
#define LEONARDO_A4 F1
#define LEONARDO_A5 F0

#define LEONARDO_D2 D1
#define LEONARDO_D4 D4

#ifdef DEBOUNCE
#    define LEEP_DEBOUNCE DEBOUNCE
#else
#    define LEEP_DEBOUNCE 5
#endif

// Number of milliseconds allowed between each state change before
// each beam path resets.
#define BEAM_STATE_TERM 2500

/*
Imagine the laser beam from an ant's eye view:

         (L,2)       (R,4)
           |           |
           |           |
          N-W    N    N-E
           |           |
(M,1)-----S-W----S----S-E----(M,1)
           |           |
           |           |
         (L,2)       (R,4)

Then, consider the buttons that we want to press:

M_tap: tap foot in the middle
R/L_hold: slide foot left or right to press a key
R/L_tap: tap foot on right or left

Finally, consider the cases in which each button should be activated:

M_tap:
  * S -> N -> S

R_tap:
  * SE -> NE -> SE
  * S -> N -> NE -> SE
  * SW -> NW -> N -> NE -> SE

R_hold:
  * S -> SE (oress)
  * SE -> [any] (unpress)

Additionally, consider each beam to be a binary bit:
M (aka S): 1
L (aka W): 2
R (aka E): 4

Therefore, the following mappings exist:

                   |  Beams Broken   |
 Value | Direction |  L  |  M  |  R  |
-------+-----------+-----+-----+-----+
   0   |    N      |     |     |     |
   1   |    S      |     |  X  |     |
   2   |    NW     |  X  |     |     |
   3   |    SW     |  X  |  X  |     |
   4   |    NE     |     |     |  X  |
   5   |    SE     |     |  X  |  X  |
   6   |  Invalid  |  X  |     |  X  |
   7   |  Invalid  |  X  |  X  |  X  |

*/

enum direction_t {
  // Values when the heel pedal is not blocked
  DIR_INVALID_0,
  DIR_HEEL_UP_S,
  DIR_INVALID_1,
  DIR_HEEL_UP_SW,
  DIR_INVALID_2,
  DIR_HEEL_UP_SE,
  DIR_INVALID_3,
  DIR_INVALID_4,
  // Values when the heel pedal is blocked (foot in default position), starts at 8
  DIR_N,
  DIR_S,
  DIR_NW,
  DIR_SW,
  DIR_NE,
  DIR_SE,
  DIR_END,
};

typedef struct {
  uint8_t path_idx;
  uint8_t matrix_row_bit;
  bool hold;
  bool activated;
  uint16_t activated_at;
  const uint8_t *path;
} beam_path_t;

#define HOLD_BEAM_PATH(matrix_bit, path_var) { .hold = true, .matrix_row_bit = matrix_bit, .path = &(path_var)[0] }

#define TAP_BEAM_PATH(matrix_bit, path_var) { .hold = false, .matrix_row_bit = matrix_bit, .path = &(path_var)[0] }

// Left
static const uint8_t PROGMEM left_hold_path[] = {DIR_S, DIR_SW, DIR_END};
// Foot tap from opposite side, from middle, and from same side
static const uint8_t PROGMEM left_tap_path_1[] = {DIR_SE, DIR_NE, DIR_N,  DIR_NW, DIR_SW, DIR_END};
static const uint8_t PROGMEM left_tap_path_2[] = {DIR_S,  DIR_N,  DIR_NW, DIR_SW, DIR_END};
static const uint8_t PROGMEM left_tap_path_3[] = {DIR_SW, DIR_NW, DIR_SW, DIR_END};

// Middle
// Foot tap from left, from middle, and from right
static const uint8_t PROGMEM middle_tap_path_1[] = {DIR_SW, DIR_NW, DIR_N, DIR_S, DIR_END};
static const uint8_t PROGMEM middle_tap_path_2[] = {DIR_S,  DIR_N,  DIR_S, DIR_END};
static const uint8_t PROGMEM middle_tap_path_3[] = {DIR_SE, DIR_NE, DIR_N, DIR_S, DIR_END};

// Right
static const uint8_t PROGMEM right_hold_path[] = {DIR_S, DIR_SE, DIR_END};
// Foot tap from opposite side, from middle, and from same side
static const uint8_t PROGMEM right_tap_path_1[] = {DIR_SW, DIR_NW, DIR_N,  DIR_NE, DIR_SE, DIR_END};
static const uint8_t PROGMEM right_tap_path_2[] = {DIR_S,  DIR_N,  DIR_NE, DIR_SE, DIR_END};
static const uint8_t PROGMEM right_tap_path_3[] = {DIR_SE, DIR_NE, DIR_SE, DIR_END};

// Heel
static const uint8_t PROGMEM heel_tap_path[] = {DIR_S, DIR_HEEL_UP_S, DIR_S, DIR_END};
// Below values are when the front of the foot is left or right and the back heel is tapped
static const uint8_t PROGMEM heel_tap_left_path[] = {DIR_SW, DIR_HEEL_UP_SW, DIR_SW, DIR_END};
static const uint8_t PROGMEM heel_tap_right_path[] = {DIR_SE, DIR_HEEL_UP_SE, DIR_SE, DIR_END};

static beam_path_t beam_paths[] = {
  // Left
  HOLD_BEAM_PATH(2, left_hold_path),
  TAP_BEAM_PATH(4, left_tap_path_1),
  TAP_BEAM_PATH(4, left_tap_path_2),
  TAP_BEAM_PATH(4, left_tap_path_3),

  // Middle
  TAP_BEAM_PATH(1, middle_tap_path_1),
  TAP_BEAM_PATH(1, middle_tap_path_2),
  TAP_BEAM_PATH(1, middle_tap_path_3),

  // Right
  HOLD_BEAM_PATH(8, right_hold_path),
  TAP_BEAM_PATH(16, right_tap_path_1),
  TAP_BEAM_PATH(16, right_tap_path_2),
  TAP_BEAM_PATH(16, right_tap_path_3),

  // Heel
  TAP_BEAM_PATH(32, heel_tap_path),
  TAP_BEAM_PATH(64, heel_tap_left_path),
  TAP_BEAM_PATH(128, heel_tap_right_path),
};

static uint8_t num_beam_paths = 0;
static enum direction_t beam_state = DIR_END;
static enum direction_t possible_next_beam_state = DIR_END;
static uint16_t beam_state_debounce_start = 0;
static bool beam_state_stale = true;
static uint16_t beam_state_changed_time = 0;

#define POWER_PIN_COUNT 1
#define INPUT_PIN_COUNT 4

static uint8_t power_pins[POWER_PIN_COUNT] = {
  LEONARDO_D2,
  // LEONARDO_D4,
};

static uint8_t input_pins[INPUT_PIN_COUNT] = {
  LEONARDO_A2, // M (1)
  LEONARDO_A3, // L (2)
  LEONARDO_A4, // R (4)
  LEONARDO_A5, // Heel (8)
};

static const uint16_t analog_press_threshold = 100;

#define POWER_PIN_DELAY_MS 2
static uint8_t current_power_pin = 0;
static uint16_t power_pin_change_time = 0;

void matrix_init_custom(void) {
  num_beam_paths = sizeof(beam_paths) / sizeof(beam_path_t);

  for (uint8_t i = 0; i < POWER_PIN_COUNT; i++) {
    setPinOutput(power_pins[i]);
    writePinLow(power_pins[i]);
  }
  writePinHigh(power_pins[current_power_pin]);
  power_pin_change_time = timer_read();

  for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {
    setPinInput(input_pins[i]);
  }
}

// Update the current beam state while considering DEBOUNCE implications
// Returns whether or not the current state has just gone stale.
bool update_beam_state(void) {

  // Check if enough time has elapsed since updating the power pins
  if (timer_elapsed(power_pin_change_time) <= POWER_PIN_DELAY_MS) {
    // If not, continue waiting
    return false;
  }

  // If enough time has passed, then check the new beam state
  // TODO: get the proper pedal to update
  enum direction_t new_beam_state = 0;
  uint8_t coef = 1;
  for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {
    bool pressed = analogReadPin(input_pins[i]) < analog_press_threshold;
    if (pressed) {
      new_beam_state += coef;
    }
    coef *= 2;
  }

  // Now that we read all of the pins, prepare for the next input.
  writePinLow(power_pins[current_power_pin]);
  current_power_pin = (current_power_pin + 1) % POWER_PIN_COUNT;
  writePinHigh(power_pins[current_power_pin]);
  power_pin_change_time = timer_read();

  /* Consider the following states (where 0, 1, and 2 are generic values for each variable

  | case | beam_state | possible_nbs | new_beam_state | outcome
  -------+------------+--------------+----------------+--------------------------------
  |  A   |     0      |      0       |       0        | do nothing
  |  B   |     0      |      0       |       1        | set possible=new, start timer
  |  C   |     0      |      1       |       0        | set possible=new, do nothing
  |  D   |     0      |      1       |       1        | check timer, and update beam if past DEBOUNCE
  |  E   |     0      |      1       |       2        | set possible=new, start timer

  This, however, can be generalized by considering the cases where possible_nbs != new_beam_state (cases B, C, and E)
  They all result in simply updating the next possible beam_state.
  */

  bool turned_stale = false;
  if (!beam_state_stale) {
    if (timer_elapsed(beam_state_changed_time) > BEAM_STATE_TERM) {
      beam_state_stale = true;
      turned_stale = true;
    }
  }

  // Cases B, C, and E
  if (possible_next_beam_state != new_beam_state) {
    possible_next_beam_state = new_beam_state;
    beam_state_debounce_start = timer_read();
    return turned_stale;
  }

  // If here, then possible_next_beam_state and new_beam_state are equal

  // Case D (0, 1, 1)
  if (beam_state != possible_next_beam_state) {
    if (timer_elapsed(beam_state_debounce_start) > LEEP_DEBOUNCE) {
      beam_state = possible_next_beam_state;
      beam_state_changed_time = timer_read();
      beam_state_stale = false;
      turned_stale = false;
    }
  }

  // Case A (0, 0, 0): do nothing
  return turned_stale;
}

bool matrix_scan_custom_fancy(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Check for activated tap keys and clear them when necessary
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];

    // TODO: unset debounce entirely (from QMK's perspective) since we do debounce handling in update_beam_state
    bool enough_time_elapsed = timer_elapsed(beam_path->activated_at) > LEEP_DEBOUNCE;
    if (!beam_path->hold && beam_path->activated && enough_time_elapsed) {
      // TODO: callback for [de]activation?
      changed = true;
      beam_path->activated = false;
      // Clear the bit (take the AND of the negation)
      current_matrix[0] &= (~(beam_path->matrix_row_bit));
    }
  }

  enum direction_t old_beam_state = beam_state;
  bool turned_stale = update_beam_state();

  if (old_beam_state == beam_state) {

    if (turned_stale) {
      for (uint8_t i = 0; i < num_beam_paths; i++) {
        beam_path_t *beam_path = &beam_paths[i];
        beam_path->path_idx = 0;
      }
    }

    return changed;
  }

  // send_word(beam_state);
  // SEND_STRING(" ");

  // Iterate over all the beam paths
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];

    // Deactivate activated paths for hold beam_paths
    if (beam_path->hold && beam_path->activated) {
      changed = true;
      beam_path->activated = false;
      // Clear the bit (take the AND of the negation)
      current_matrix[0] &= (~(beam_path->matrix_row_bit));
    }

    // Update the beam_path's state
    if (beam_state == pgm_read_byte(&beam_path->path[beam_path->path_idx])) {
      beam_path->path_idx++;
    } else {
      beam_path->path_idx = 0;
      continue;
    }


    // Activate
    if (pgm_read_byte(&beam_path->path[beam_path->path_idx]) == DIR_END) {
      changed = true;
      beam_path->activated = true;
      beam_path->activated_at = timer_read();

      // Activate the key
      current_matrix[0] |= beam_path->matrix_row_bit;

      // If last state is same as first state, start at next index
      // Note: this implies that a `hold` beam_path can't have the same first and last state
      if (beam_state == pgm_read_byte(&beam_path->path[0])) {
        beam_path->path_idx = 1;
      } else {
        beam_path->path_idx = 0;
      }
    }
  }

  return changed;
}

bool matrix_scan_custom_regular(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Iterate over all the pedals
  uint16_t matrix_row_bit = 1;
  for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {

    bool pressed = analogReadPin(input_pins[i]) < analog_press_threshold;
    if ((!!(current_matrix[0] & matrix_row_bit)) != (pressed)) {
      // Take the XOR of the bit (which always flip that bit)
      current_matrix[0] ^= matrix_row_bit;
      changed = true;
    }
    matrix_row_bit <<= 1;
  }

  return changed;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  // return matrix_scan_custom_regular(current_matrix);
  return matrix_scan_custom_fancy(current_matrix);
}
