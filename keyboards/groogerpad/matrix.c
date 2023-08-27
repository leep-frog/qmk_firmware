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


void led_blink(int times) {
  for (int i = 0; i < times; i++) {
    led_on();
    wait_ms(blink_time);
    led_off();
    wait_ms(blink_time);
  }
}

void matrix_init_custom(void) {
  uart_init(9600);
  xprintf("Initializing groog controller");
  xprintf("Initing");
  setPinOutput(D4);

  // Clear the buffer;
  while (uart_available()) {
    uart_read();
  }

  // Wait until the other board starts first (to avoid both blocking issue);
  // TODO: find a better way to avoid this behavior
  wait_ms(5000);

  led_blink(4);
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
  BUTTON_MAPPING(4, 1), // A
  BUTTON_MAPPING(3, 4), // B
  BUTTON_MAPPING(3, 3), // X
  BUTTON_MAPPING(2, 1), // Y
  BUTTON_MAPPING(1, 0), // LB
  BUTTON_MAPPING(1, 1), // RB
  // IGNORE_BUTTON(),      // LT (get fuller data from other buttons)
  // IGNORE_BUTTON(),      // RT ^^^
  BUTTON_MAPPING(3, 0), // Left joystick click
  BUTTON_MAPPING(5, 2), // Left joystick click
};

const uint8_t NUM_BUTTONS = sizeof(button_mappings) / sizeof(button_mappings[0]);

button_mapping_t misc_button_mappings[] = {
  BUTTON_MAPPING(2, 0), // Xbox button
  BUTTON_MAPPING(3, 1), // Select
  BUTTON_MAPPING(3, 2), // Start
};

const uint8_t NUM_MISC_BUTTONS = sizeof(misc_button_mappings) / sizeof(misc_button_mappings[0]);

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Request data
  uart_write(1);

  // Receive data
  nina_gamepad_t gamepad;
  uart_receive((uint8_t *)(&gamepad), sizeof(nina_gamepad_t));

  // Process regular buttons
  uint16_t button_mask = gamepad.buttons;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    button_mapping_t bm = button_mappings[i];
    // If the key is marked as pressed
    bool gamepad_pressed = !!(button_mask & 1);
    bool key_pressed = !!(current_matrix[bm.kb_matrix_row] & (bm.kb_matrix_row_bit));

    // Toggle the bit if they don't match.
    if (key_pressed != gamepad_pressed) {
      current_matrix[bm.kb_matrix_row] ^= (bm.kb_matrix_row_bit);
      changed = true;
    }
    button_mask >>= 1;
  }

  // Process misc buttons
  uint16_t misc_button_mask = gamepad.misc_buttons;
  for (int i = 0; i < NUM_MISC_BUTTONS; i++) {
    button_mapping_t bm = misc_button_mappings[i];
    // If the key is marked as pressed
    bool gamepad_pressed = !!(misc_button_mask & 1);
    bool key_pressed = !!(current_matrix[bm.kb_matrix_row] & (bm.kb_matrix_row_bit));

    // Toggle the bit if they don't match.
    if (key_pressed != gamepad_pressed) {
      current_matrix[bm.kb_matrix_row] ^= (bm.kb_matrix_row_bit);
      changed = true;
    }
    misc_button_mask >>= 1;
  }
  return changed;
}
