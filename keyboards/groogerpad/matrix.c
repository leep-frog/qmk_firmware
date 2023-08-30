#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "uart.h"
#include "timer.h"
#include "print.h"

const int blink_time = 125;

void led_on(void) {
  writePinHigh(D4);
}

void led_off(void) {
  writePinLow(D4);
}

__attribute__((weak)) void handle_left_stick(int32_t axis_x, int32_t axis_y) {
}


void led_blink(int times) {
  for (int i = 0; i < times; i++) {
    led_on();
    wait_ms(blink_time);
    led_off();
    wait_ms(blink_time);
  }
}

void matrix_init_custom(void) {
  uart_init(115200);
  xprintf("Initializing groog controller");
  xprintf("Initing");
  setPinOutput(D4);

  // Clear the buffer;
  while (uart_available()) {
    uart_read();
  }

  led_blink(4);
}

#define CHECK_BUTTON(button, var, pos) ((var) & (1<<(pos)))

// Copied from (TODO link);
typedef struct __attribute__((packed)) {
  // Usage Page: 0x01 (Generic Desktop Controls)
  uint8_t dpad;
  // -512 to 512 (or 511)
  int32_t axis_x;
  int32_t axis_y;
  int32_t axis_rx;
  int32_t axis_ry;

  // Usage Page: 0x02 (Sim controls)
  // 0 to 1024
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
  uint8_t kb_matrix_row;
  // 0-indexed bit position starting at the least-significant bit
  uint8_t kb_matrix_row_bit;
  bool ignore;
} button_mapping_t;

#define BUTTON_MAPPING(matrix_row, matrix_col) {matrix_row, 1 << matrix_col, false}
#define IGNORE_BUTTON() {0, 0, true}

// This maps button bit order (least-significant bit first)
// to [matrix_row, offset]
button_mapping_t button_mappings[] = {
  // Ordering determined from here:
  // https://github.com/ricardoquesada/bluepad32-arduino/blob/b026e813baf386fab596d4dc247afe268b79e40a/src/Controller.h#L71
  BUTTON_MAPPING(3, 1), // A
  BUTTON_MAPPING(2, 4), // B
  BUTTON_MAPPING(2, 3), // X
  BUTTON_MAPPING(1, 1), // Y
  BUTTON_MAPPING(0, 0), // LB
  BUTTON_MAPPING(0, 1), // RB
  IGNORE_BUTTON(),      // LT (get fuller data from other buttons)
  IGNORE_BUTTON(),      // RT ^^^
  BUTTON_MAPPING(2, 0), // Left joystick click
  BUTTON_MAPPING(4, 2), // Right joystick click
};

#define GET_NUM_BUTTONS(arr) sizeof( arr ) / sizeof( arr[0] )

const uint8_t NUM_BUTTONS = GET_NUM_BUTTONS(button_mappings);

button_mapping_t misc_button_mappings[] = {
  BUTTON_MAPPING(1, 0), // Xbox button
  BUTTON_MAPPING(2, 1), // Select
  BUTTON_MAPPING(2, 2), // Start
};

const uint8_t NUM_MISC_BUTTONS = GET_NUM_BUTTONS(misc_button_mappings);

// TODO: Join dpad and misc buttons for smaller data packets
button_mapping_t dpad_button_mappings[] = {
  BUTTON_MAPPING(3, 0), // Up
  BUTTON_MAPPING(5, 0), // Down
  BUTTON_MAPPING(4, 1), // Right
  BUTTON_MAPPING(4, 0), // Left
};

const uint8_t NUM_DPAD_BUTTONS = GET_NUM_BUTTONS(dpad_button_mappings);

bool process_button_mask(matrix_row_t current_matrix[], button_mapping_t bms[], uint16_t button_mask, uint8_t size) {
  bool changed = false;
  for (int i = 0; i < size; i++) {
    button_mapping_t bm = bms[i];
    if (bm.ignore) {
      button_mask >>= 1;
      continue;
    }
    // If the key is marked as pressed
    bool gamepad_pressed = !!(button_mask & 0x01);
    bool key_pressed = !!(current_matrix[bm.kb_matrix_row] & (bm.kb_matrix_row_bit));

    // Toggle the bit if they don't match.
    if (key_pressed != gamepad_pressed) {
      current_matrix[bm.kb_matrix_row] ^= (bm.kb_matrix_row_bit);
      changed = true;
    }
    button_mask >>= 1;
  }
  return changed;
}

nina_gamepad_t gamepad;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Request data
  uart_write(1);

  // Receive data
  uart_receive((uint8_t *)(&gamepad), sizeof(nina_gamepad_t));

  /*if (gamepad.buttons) {
    led_on();
  } else {
    led_off();
  }*/

  // Process regular buttons
  if (process_button_mask(current_matrix, button_mappings, gamepad.buttons, NUM_BUTTONS)) {
    changed = true;
  }
  if (process_button_mask(current_matrix, misc_button_mappings, gamepad.misc_buttons, NUM_MISC_BUTTONS)) {
    changed = true;
  }
  if (process_button_mask(current_matrix, dpad_button_mappings, gamepad.dpad, NUM_DPAD_BUTTONS)) {
    changed = true;
  }

  return changed;
}

#include "./groogermouse.c"
