#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "uart.h"
#include "timer.h"
#include "print.h"
#include "groogerpad.h"

// Max is 1023
const int trigger_threshold = 900;

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

// Copied from (https://github.com/ricardoquesada/bluepad32-arduino/blob/b026e813baf386fab596d4dc247afe268b79e40a/src/ControllerData.h#L20-L40);
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
  // data that needs to be sent and remove these (note these were
  // also removed in the Bluepad32 code for the sending library).
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
  BUTTON_MAPPING(4, 2), // A
  BUTTON_MAPPING(3, 4), // B
  BUTTON_MAPPING(3, 3), // X
  BUTTON_MAPPING(2, 1), // Y
  BUTTON_MAPPING(1, 0), // LB
  BUTTON_MAPPING(1, 1), // RB
  IGNORE_BUTTON(),      // LT (get fuller data from other buttons)
  IGNORE_BUTTON(),      // RT ^^^
  BUTTON_MAPPING(3, 0), // Left joystick click
  BUTTON_MAPPING(5, 2), // Right joystick click
};

#define GET_NUM_BUTTONS(arr) sizeof( arr ) / sizeof( arr[0] )

const uint8_t NUM_BUTTONS = GET_NUM_BUTTONS(button_mappings);

button_mapping_t misc_button_mappings[] = {
  // Note: the Xbox button only works on newer controllers (that have the additional small button sorta in between select and start)
  // See this issue for addition of logic on controllers for older models: https://github.com/ricardoquesada/bluepad32-arduino/issues/7
  BUTTON_MAPPING(2, 0), // Xbox button
  BUTTON_MAPPING(3, 1), // Select
  BUTTON_MAPPING(3, 2), // Start
  BUTTON_MAPPING(4, 1), // Extra button
};

const uint8_t NUM_MISC_BUTTONS = GET_NUM_BUTTONS(misc_button_mappings);

// I initially had the idea to combine all of the following bitmasks to save on space:
// * buttons (10 out of 16 bits used)
// * misc_buttons (3 out of 8 bits used)
// * dpad_buttons (4 out of 8 bits used)
// * * * * Total: (17 out of 32 bits used)
// As the math shows, we would have to rework a lot more to actually save space (since options are 1 bytes or 2 bytes).
// Try to do something clever here isn't worth the work, savings, or risk of causing other issues.
button_mapping_t dpad_button_mappings[] = {
  BUTTON_MAPPING(4, 0), // Up
  BUTTON_MAPPING(6, 0), // Down
  BUTTON_MAPPING(5, 1), // Right
  BUTTON_MAPPING(5, 0), // Left
};

const uint8_t NUM_DPAD_BUTTONS = GET_NUM_BUTTONS(dpad_button_mappings);

#define CHECK_KEY_BIT(activated, matrix_row, matrix_row_bit) \
/*  (           pressed_in_matrix                     ) != (activated) */ \
if ((!!(current_matrix[matrix_row] & (matrix_row_bit))) != (activated)) { \
current_matrix[matrix_row] ^= (matrix_row_bit); \
changed = true; \
}

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
    CHECK_KEY_BIT(gamepad_pressed, bm.kb_matrix_row, bm.kb_matrix_row_bit)
    button_mask >>= 1;
  }
  return changed;
}

nina_gamepad_t gamepad;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;

  // Only request data if there isn't anything already available
  UART_WRITE_SEND_DATA();
  uint16_t last_write = timer_read();
  while (!uart_available()) {
    // Send more data in case the previous packet got sent
    // before the other circuit board started
    if (timer_elapsed(last_write) >= 2500) {
      led_blink(2);
      UART_WRITE_SEND_DATA();
      last_write = timer_read();
    }
  }
  uart_receive((uint8_t *)(&gamepad), sizeof(nina_gamepad_t));
  // Clear any extra data in the buffer, if relevant
  while (uart_available()) {
    uart_receive((uint8_t *)(&gamepad), sizeof(nina_gamepad_t));
  }

  if (gamepad.buttons) {
    led_on();
  } else {
    led_off();
  }

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

  // Left and right triggers
  CHECK_KEY_BIT(gamepad.brake >= trigger_threshold, 0, 1)
  CHECK_KEY_BIT(gamepad.throttle >= trigger_threshold, 0, 2)

  return changed;
}

#include "./groogermouse.c"
