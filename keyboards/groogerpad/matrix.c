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
  BUTTON_MAPPING(4, 1), // A
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
  BUTTON_MAPPING(2, 0), // Xbox button
  BUTTON_MAPPING(3, 1), // Select
  BUTTON_MAPPING(3, 2), // Start
};

const uint8_t NUM_MISC_BUTTONS = GET_NUM_BUTTONS(misc_button_mappings);

// TODO: Join dpad and misc buttons for smaller data packets
button_mapping_t dpad_button_mappings[] = {
  BUTTON_MAPPING(4, 0), // Up
  BUTTON_MAPPING(6, 0), // Down
  BUTTON_MAPPING(5, 1), // Right
  BUTTON_MAPPING(5, 0), // Left
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

  bool turn_on_led = false;

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

  if (turn_on_led) {
    led_on();
  } else {
    led_off();
  }
  return changed;
}

/***************
 * Mouse logic *
 ***************/

const int intBufLen = 18;

void print_int(int32_t number) {
  char intBuf[intBufLen];
  int i = 0;
  // TODO: Reverse buffer afterwards
  for (; number > 0; i++) {
    intBuf[i] = '0' + (number % 10);
    number /= 10;
  }
  intBuf[i+1] = 'X';
  intBuf[i+2] = '\n';
  intBuf[i+3] = '\0';
  send_string(intBuf);
}


const int mouse_denom = 256;

bool pointing_device_task(void) {
    // motion_delta_t delta = readSensor();

    report_mouse_t report = pointing_device_get_report();

    /*if(delta.motion_ind) {
        // clamp deltas from -127 to 127
        report.x = delta.delta_x < -127 ? -127 : delta.delta_x > 127 ? 127 : delta.delta_x;
        report.x = -report.x;
        report.y = delta.delta_y < -127 ? -127 : delta.delta_y > 127 ? 127 : delta.delta_y;
    }*/

    // 4x multiplier

    // axis_x goes from -512 to 512 (actually like +-511)

    report.x = gamepad.axis_x / mouse_denom;
    report.y = gamepad.axis_y / mouse_denom;
    // TODO: Use gamepad.throttle

    pointing_device_set_report(report);
    return pointing_device_send();
}

// report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
//   if (gamepad.buttons) {
//     SEND_STRING("o");
//     mouse_report.x = 10;
//   } else {
//     mouse_report.x = -10;
//   }
//   // mouse_report.x = gamepad.axis_x / 10;
//   return mouse_report;
// }
