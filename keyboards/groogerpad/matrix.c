#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "uart.h"
#include "timer.h"
#include "print.h"


void matrix_init_custom(void) {
  uart_init(9600);
  xprintf("Initializing groog controller");
  xprintf("Initing");
}

#define CHECK_BUTTON(button, var, pos) ((var) & (1<<(pos)))

// Copied from (TODO link);
typedef struct __attribute__((packed)) {
  // Usage Page: 0x01 (Generic Desktop Controls)
  uint8_t dpad;
  int32_t axis_x;
  int32_t axis_y;
  int32_t axis_rx;
  int32_t axis_ry;

  // Usage Page: 0x02 (Sim controls)
  int32_t brake;
  int32_t throttle;

  // Usage Page: 0x09 (Button)
  uint16_t buttons;

  // Misc buttons (from 0x0c (Consumer) and others)
  uint8_t misc_buttons;

  // Xbox controller doesn't have any accelerometer, so save
  // data that needs to be sent and remove these.
  /*int32_t gyro[3];
  int32_t accel[3];*/
} nina_gamepad_t;

typedef struct {
  // 0-indexed bit position starting at the least-significant bit
  uint8_t gamepad_button_bit;
  uint8_t kb_matrix_row;
  // 0-indexed bit position starting at the least-significant bit
  uint8_t kb_matrix_row_bit;
} button_mapping_t;

// This maps button bit order (least-significant bit first)
// to [matrix_row, offset]
button_mapping_t button_mappings[] = {
  // A
  {1, 4, 2},
};

bool blop = false;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  if (uart_available()) {
    xprintf("Loading controller");
    nina_gamepad_t gamepad;
    uart_receive((uint8_t *)(&gamepad), sizeof(nina_gamepad_t));
    uint16_t button_mask = gamepad.buttons;

    bool changed = false;
    if (blop) {
      send_byte(button_mappings[0].gamepad_button_bit);
      send_byte((uint8_t)button_mask);
    }
    for (int i = 0; i < 1; i++) {
      button_mapping_t bm = button_mappings[i];
      // If the key is marked as pressed
      bool gamepad_pressed = !!(((uint8_t)button_mask) & (bm.gamepad_button_bit));
      bool key_pressed = !!(current_matrix[bm.kb_matrix_row] & (bm.kb_matrix_row_bit));

      // Toggle the bit if they don't match.
      if (key_pressed != gamepad_pressed) {
        current_matrix[bm.kb_matrix_row] ^= (bm.kb_matrix_row_bit);
        changed = true;
      }
    }
    return changed;
  }

  return false;
}
