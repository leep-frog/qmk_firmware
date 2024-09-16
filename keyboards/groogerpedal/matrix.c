#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "analog.h"

#ifdef DEBOUNCE
#    define LEEP_DEBOUNCE DEBOUNCE
#else
#    define LEEP_DEBOUNCE 5
#endif

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
  // Values when the back pedal is not blocked
  DIR_INVALID_0,
  DIR_HEEL_UP, // Value is 1 since only the middle beam is blocked
  DIR_INVALID_2,
  DIR_INVALID_3,
  DIR_INVALID_4,
  DIR_INVALID_5,
  DIR_INVALID_6,
  DIR_INVALID_7,
  // Values when the back pedal is blocked (foot in default position), starts at 8
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
  // TODO: Timeout info
  bool activated;
  uint16_t activated_at;
  const uint8_t *path;
} beam_path_t;

#define HOLD_BEAM_PATH(matrix_bit, path_var) { .hold = true, .matrix_row_bit = matrix_bit, .path = &(path_var)[0] }

#define TAP_BEAM_PATH(matrix_bit, path_var) { .hold = false, .matrix_row_bit = matrix_bit, .path = &(path_var)[0] }

// Left
const uint8_t PROGMEM left_hold_path[] = {DIR_S, DIR_SW, DIR_END};
// Foot tap from opposite side, from middle, and from same side
const uint8_t PROGMEM left_tap_path_1[] = {DIR_SE, DIR_NE, DIR_N,  DIR_NW, DIR_SW, DIR_END};
const uint8_t PROGMEM left_tap_path_2[] = {DIR_S,  DIR_N,  DIR_NW, DIR_SW, DIR_END};
const uint8_t PROGMEM left_tap_path_3[] = {DIR_SW, DIR_NW, DIR_SW, DIR_END};

// Middle
const uint8_t PROGMEM middle_tap_path[] = {DIR_S, DIR_N, DIR_S, DIR_END};

// Right
const uint8_t PROGMEM right_hold_path[] = {DIR_S, DIR_SE, DIR_END};
// Foot tap from opposite side, from middle, and from same side
const uint8_t PROGMEM right_tap_path_1[] = {DIR_SW, DIR_NW, DIR_N,  DIR_NE, DIR_SE, DIR_END};
const uint8_t PROGMEM right_tap_path_2[] = {DIR_S,  DIR_N,  DIR_NE, DIR_SE, DIR_END};
const uint8_t PROGMEM right_tap_path_3[] = {DIR_SE, DIR_NE, DIR_SE, DIR_END};

// Heel
const uint8_t PROGMEM heel_tap_path[] = {DIR_S, DIR_HEEL_UP, DIR_S, DIR_END};

beam_path_t beam_paths[] = {
  // Left
  HOLD_BEAM_PATH(2, left_hold_path),
  TAP_BEAM_PATH(4, left_tap_path_1),
  TAP_BEAM_PATH(4, left_tap_path_2),
  TAP_BEAM_PATH(4, left_tap_path_3),

  // Middle
  TAP_BEAM_PATH(1, middle_tap_path),

  // Right
  HOLD_BEAM_PATH(8, right_hold_path),
  TAP_BEAM_PATH(16, right_tap_path_1),
  TAP_BEAM_PATH(16, right_tap_path_2),
  TAP_BEAM_PATH(16, right_tap_path_3),

  // Heel
  TAP_BEAM_PATH(32, heel_tap_path),
};

uint8_t num_beam_paths = 0;
enum direction_t beam_state = DIR_END;
enum direction_t possible_next_beam_state = DIR_END;
uint16_t beam_state_change_time = 0;

uint8_t pedal_pins[] = {
  F0, // M (1)
  F1, // L (2)
  F5, // R (4)
  F4, // Back (8)
};

uint8_t num_pedals = 0;
const uint16_t analog_press_threshold = 125;

void matrix_init_custom(void) {
  num_beam_paths = sizeof(beam_paths) / sizeof(beam_path_t);
  num_pedals = sizeof(pedal_pins) / sizeof(uint8_t);

  for (uint8_t i = 0; i < num_pedals; i++) {
    setPinInput(pedal_pins[i]);
  }
}

// Update the current beam state while considering DEBOUNCE implications
void update_beam_state(void) {

  enum direction_t new_beam_state = 0;
  uint8_t coef = 1;
  for (uint8_t i = 0; i < num_pedals; i++) {
    bool pressed = analogReadPin(pedal_pins[i]) < analog_press_threshold;
    if (pressed) {
      new_beam_state += coef;
    }
    coef *= 2;
  }

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

  // Cases B, C, and E
  if (possible_next_beam_state != new_beam_state) {
    possible_next_beam_state = new_beam_state;
    beam_state_change_time = timer_read();
    return;
  }

  // If here, then possible_next_beam_state and new_beam_state are equal

  // Case D (0, 1, 1)
  if (beam_state != possible_next_beam_state) {
    if (timer_elapsed(beam_state_change_time) > LEEP_DEBOUNCE) {
      beam_state = possible_next_beam_state;
    }
  }

  // Case A (0, 0, 0): do nothing
}

bool matrix_scan_custom_fancy(matrix_row_t current_matrix[]) {
  bool changed = false;

  // TODO: Check for activated keys (with timers so hold=false) and clear the bits (use DEBOUNCE+1 for time delay)
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];

    bool enough_time_elapsed = timer_elapsed(beam_path->activated_at) > LEEP_DEBOUNCE;
    if (!beam_path->hold && beam_path->activated && enough_time_elapsed) {
      // TODO: macro for [de]activation
      changed = true;
      beam_path->activated = false;
      // Clear the bit (take the AND of the negation)
      current_matrix[0] &= (~(beam_path->matrix_row_bit));
    }
  }

  enum direction_t old_beam_state = beam_state;
  update_beam_state();

  // TODO: Check back pedal

  if (old_beam_state == beam_state) {
    return changed;
  }

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

    uint8_t want = pgm_read_byte(&beam_path->path[beam_path->path_idx]);

    // Update the beam_path's state
    if (beam_state == want) {
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
  for (uint8_t i = 0; i < num_pedals; i++) {

    bool pressed = analogReadPin(pedal_pins[i]) < analog_press_threshold;
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
