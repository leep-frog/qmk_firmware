#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "analog.h"

uint8_t pedal_pins[] = {
  F0,
  F1,
  F4,
  F5,
};

uint8_t num_pedals = 0;
const uint16_t analog_press_threshold = 125;

void matrix_init_custom(void) {
  num_pedals = sizeof(pedal_pins) / sizeof(uint8_t);

  for (uint8_t i = 0; i < num_pedals; i++) {
    setPinInput(pedal_pins[i]);
  }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
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
