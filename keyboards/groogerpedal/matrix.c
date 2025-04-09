#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "analog.h"
#include "groogerpedal.h"

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

// Custom debounce logic is implemented so we use this custom debounce value
// (and set DEBOUNCE to 0 in config.h)
#define LEEP_DEBOUNCE 20

#define POWER_PIN_COUNT 2
#define INPUT_PIN_COUNT 5

static uint8_t power_pins[POWER_PIN_COUNT] = {
  LEONARDO_D2,
  LEONARDO_D4,
};

static uint8_t input_pins[INPUT_PIN_COUNT] = {
  LEONARDO_A5, // M (1)
  LEONARDO_A4, // L (2)
  LEONARDO_A2, // R (4)
  LEONARDO_A3, // Heel (8)
  LEONARDO_A1, // Front (16)
};

// This is the analog read value that needs to be registered in order to count
// the beam as unbroken (out of 1024).
static const uint16_t analog_press_threshold = 500;

// Number of milliseconds allowed between each state change before
// each beam path resets.
#ifndef BEAM_STATE_TERM
#    define BEAM_STATE_TERM 300
#endif


typedef struct {
  uint8_t path_idx;
  bool activated;
  uint16_t activated_at;
} pedal_beam_state_t;

typedef struct {
  uint16_t matrix_row_bit;
  bool hold;
  const uint8_t *path;
  pedal_beam_state_t pedal_beam_states[POWER_PIN_COUNT];
} beam_path_t;

// Note: pedal_beam_states is initialized in matrix_init_custom
#define HOLD_BEAM_PATH(matrix_bit_idx, path_var) { .hold = true, .matrix_row_bit = (1 << matrix_bit_idx), .path = &(path_var)[0] }
#define TAP_BEAM_PATH(matrix_bit_idx, path_var) { .hold = false, .matrix_row_bit = (1 << matrix_bit_idx), .path = &(path_var)[0] }

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

// Forward position
// Heel beams connects and then front beam breaks
static const uint8_t PROGMEM forward_path[] = {DIR_S, DIR_HEEL_UP_S, DIR_FORWARD, DIR_END};
static const uint8_t PROGMEM forward_tap_path[] = {DIR_FORWARD, DIR_HEEL_UP_S, DIR_FORWARD, DIR_END};
static const uint8_t PROGMEM forward_heel_tap_path[] = {DIR_FORWARD, DIR_FORWARD_HEEL_UP, DIR_FORWARD, DIR_END};

static beam_path_t beam_paths[] = {
  // Left
  HOLD_BEAM_PATH(3, left_hold_path),
  TAP_BEAM_PATH(0, left_tap_path_1),
  TAP_BEAM_PATH(0, left_tap_path_2),
  TAP_BEAM_PATH(0, left_tap_path_3),

  // Middle
  TAP_BEAM_PATH(1, middle_tap_path_1),
  TAP_BEAM_PATH(1, middle_tap_path_2),
  TAP_BEAM_PATH(1, middle_tap_path_3),

  // Right
  HOLD_BEAM_PATH(4, right_hold_path),
  TAP_BEAM_PATH(2, right_tap_path_1),
  TAP_BEAM_PATH(2, right_tap_path_2),
  TAP_BEAM_PATH(2, right_tap_path_3),

  // Heel
  TAP_BEAM_PATH(5, heel_tap_left_path),
  TAP_BEAM_PATH(6, heel_tap_path),
  TAP_BEAM_PATH(7, heel_tap_right_path),

  // Front
  TAP_BEAM_PATH(8, forward_tap_path),
  TAP_BEAM_PATH(9, forward_path),
  TAP_BEAM_PATH(10, forward_heel_tap_path),
};

static uint8_t num_beam_paths = 0;

typedef struct {
  direction_t beam_state;
  direction_t possible_next_beam_state;
  uint16_t beam_state_debounce_start;
  bool beam_state_stale;
  uint16_t beam_state_changed_time;
} pedal_state_t;

#define INIT_PEDAL_STATE() { .beam_state = DIR_END, .possible_next_beam_state = DIR_END, .beam_state_debounce_start = 0, .beam_state_stale = true, .beam_state_changed_time = 0}

static pedal_state_t pedal_states[POWER_PIN_COUNT] = {
  // Note, the initialization values are set in matrix_init_custom
  // That way, we don't have to add lines here if POWER_PIN_COUNT is changed
};

#define POWER_PIN_DELAY_MS 2
static uint8_t current_power_pin = 0;
static uint16_t power_pin_change_time = 0;

__attribute__ ((weak)) void handle_beam_state_change (uint8_t pedal_idx, direction_t from, direction_t to) {
  return;
}

void matrix_init_custom(void) {
  num_beam_paths = sizeof(beam_paths) / sizeof(beam_path_t);

  for (uint8_t i = 0; i < POWER_PIN_COUNT; i++) {
    setPinOutput(power_pins[i]);
    writePinLow(power_pins[i]);

    pedal_state_t *pedal_state = &pedal_states[i];
    pedal_state->beam_state = DIR_END;
    pedal_state->possible_next_beam_state = DIR_END;
    pedal_state->beam_state_debounce_start = timer_read();
    pedal_state->beam_state_stale = true;
    pedal_state->beam_state_changed_time = timer_read();
  }
  writePinHigh(power_pins[current_power_pin]);
  power_pin_change_time = timer_read();

  for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {
    setPinInput(input_pins[i]);
  }

  // Set the pedal beam states
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];
    for (uint8_t j = 0; j < POWER_PIN_COUNT; j++) {
      pedal_beam_state_t *pedal_beam_state = &beam_path->pedal_beam_states[j];
      pedal_beam_state->path_idx = 0;
      pedal_beam_state->activated = false;
      pedal_beam_state->activated_at = timer_read();
    }
  }
}

direction_t calculate_pedal_beam_state(void) {
  direction_t cur_beam_state = 0;
  uint8_t coef = 1;
  for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {
    bool pressed = analogReadPin(input_pins[i]) < analog_press_threshold;
    if (pressed) {
      cur_beam_state += coef;
    }
    coef *= 2;
  }
  return cur_beam_state;
}

// Update the current beam state while considering DEBOUNCE implications
// Returns whether or not the current state has just gone stale.
bool update_beam_state(pedal_state_t *pedal_state, direction_t new_beam_state) {

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
  if (!pedal_state->beam_state_stale) {
    if (timer_elapsed(pedal_state->beam_state_changed_time) > BEAM_STATE_TERM) {
      pedal_state->beam_state_stale = true;
      turned_stale = true;
    }
  }

  // Cases B, C, and E
  if (pedal_state->possible_next_beam_state != new_beam_state) {
    pedal_state->possible_next_beam_state = new_beam_state;
    pedal_state->beam_state_debounce_start = timer_read();
    return turned_stale;
  }

  // If here, then possible_next_beam_state and new_beam_state are equal

  // Case D (0, 1, 1)
  if (pedal_state->beam_state != pedal_state->possible_next_beam_state) {
    if (timer_elapsed(pedal_state->beam_state_debounce_start) > LEEP_DEBOUNCE) {
      pedal_state->beam_state = pedal_state->possible_next_beam_state;
      pedal_state->beam_state_changed_time = timer_read();
      pedal_state->beam_state_stale = false;
      turned_stale = false;
    }
  }

  // Case A (0, 0, 0): do nothing
  return turned_stale;
}

// We previously had to enusre this was greater than DEBOUNCE, but that feature
// has been disabled by setting DEBOUNCE to 0 in config.h. Now, we only need
// to ensure a key is activated for at least COMBO_TERM so that combos work
// across taps. Previously, a tap on the left and right pedals would trigger
// disjointly (press A, release A, press B, release B) which would prevent
// the combo from firing. By setting this, we allow for A to be held longer
// so we get (press A, press B, release A, release B).
// const uint16_t ACTIVATE_FOR = DEBOUNCE > COMBO_TERM ? DEBOUNCE : COMBO_TERM;
const uint16_t ACTIVATE_FOR = COMBO_TERM;

bool matrix_scan_custom_fancy(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Check for activated tap keys and clear them when necessary
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];

    for (uint8_t j = 0; j < POWER_PIN_COUNT; j++) {
      pedal_beam_state_t *pedal_beam_state = &beam_path->pedal_beam_states[j];

      // TODO: unset debounce entirely (from QMK's perspective) since we do debounce handling in update_beam_state
      bool enough_time_elapsed = timer_elapsed(pedal_beam_state->activated_at) > ACTIVATE_FOR;
      if (!beam_path->hold && pedal_beam_state->activated && enough_time_elapsed) {
        changed = true;
        pedal_beam_state->activated = false;
        // Clear the bit (take the AND of the negation)
        direction_t from = current_matrix[j];
        current_matrix[j] &= (~(beam_path->matrix_row_bit));
        handle_beam_state_change(j, from, current_matrix[j]);
      }
    }
  }

  // Check if enough time has elapsed since updating the power pins
  if (timer_elapsed(power_pin_change_time) <= POWER_PIN_DELAY_MS) {
    // If not, continue waiting
    return changed;
  }

  // If enough time has passed, then check the new beam state
  direction_t new_beam_state = calculate_pedal_beam_state();

  // Now that we read all of the pins, prepare for the next input.
  uint8_t pedal_beam_state_idx = current_power_pin;
  writePinLow(power_pins[current_power_pin]);
  current_power_pin = (current_power_pin + 1) % POWER_PIN_COUNT;
  writePinHigh(power_pins[current_power_pin]);
  power_pin_change_time = timer_read();

  pedal_state_t *pedal_state = &pedal_states[pedal_beam_state_idx];
  direction_t old_beam_state = pedal_state->beam_state;
  bool turned_stale = update_beam_state(pedal_state, new_beam_state);

  if (old_beam_state == pedal_state->beam_state) {

    if (turned_stale) {
      for (uint8_t i = 0; i < num_beam_paths; i++) {
        beam_path_t *beam_path = &beam_paths[i];
        pedal_beam_state_t *pedal_beam_state = &beam_path->pedal_beam_states[pedal_beam_state_idx];
        if (pedal_state->beam_state == pgm_read_byte(&beam_path->path[0])) {
          pedal_beam_state->path_idx = 1;
        } else {
          pedal_beam_state->path_idx = 0;
        }
      }
    }

    return changed;
  }

  // send_word(pedal_state->beam_state);
  // SEND_STRING(" ");

  // Iterate over all the beam paths
  for (uint8_t i = 0; i < num_beam_paths; i++) {
    beam_path_t *beam_path = &beam_paths[i];
    pedal_beam_state_t *pedal_beam_state = &beam_path->pedal_beam_states[pedal_beam_state_idx];

    // Deactivate activated paths for hold beam_paths
    if (beam_path->hold && pedal_beam_state->activated) {
      changed = true;
      pedal_beam_state->activated = false;
      // Clear the bit (take the AND of the negation)
      direction_t from = current_matrix[pedal_beam_state_idx];
      current_matrix[pedal_beam_state_idx] &= (~(beam_path->matrix_row_bit));
      handle_beam_state_change(pedal_beam_state_idx, from, current_matrix[pedal_beam_state_idx]);
    }

    // Update the beam_path's state
    if (pedal_state->beam_state == pgm_read_byte(&beam_path->path[pedal_beam_state->path_idx])) {
      pedal_beam_state->path_idx++;
    } else {
      pedal_beam_state->path_idx = 0;
      continue;
    }


    // Activate
    if (pgm_read_byte(&beam_path->path[pedal_beam_state->path_idx]) == DIR_END) {
      changed = true;
      pedal_beam_state->activated = true;
      pedal_beam_state->activated_at = timer_read();

      // Activate the key
      direction_t from = current_matrix[pedal_beam_state_idx];
      current_matrix[pedal_beam_state_idx] |= beam_path->matrix_row_bit;
      handle_beam_state_change(pedal_beam_state_idx, from, current_matrix[pedal_beam_state_idx]);

      // If last state is same as first state, start at next index
      // Note: this implies that a `hold` beam_path can't have the same first and last state
      if (pedal_state->beam_state == pgm_read_byte(&beam_path->path[0])) {
        pedal_beam_state->path_idx = 1;
      } else {
        pedal_beam_state->path_idx = 0;
      }
    }
  }

  return changed;
}

// bool matrix_scan_custom_regular(matrix_row_t current_matrix[]) {
//   bool changed = false;

//   // Iterate over all the pedals
//   uint16_t matrix_row_bit = 1;
//   for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {

//     bool pressed = analogReadPin(input_pins[i]) < analog_press_threshold;
//     if ((!!(current_matrix[0] & matrix_row_bit)) != (pressed)) {
//       // Take the XOR of the bit (which always flip that bit)
//       current_matrix[0] ^= matrix_row_bit;
//       changed = true;
//     }
//     matrix_row_bit <<= 1;
//   }

//   return changed;
// }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  // return matrix_scan_custom_regular(current_matrix);
  return matrix_scan_custom_fancy(current_matrix);
}
