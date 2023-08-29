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

/* Mouse speed logic description

Mouse speed per cycle = controller_speed * (max_virtual_mouse_speed / max_controller_speed) * (throttle_multiplier_effect[1]) * (virtual_mouse_granularity_effect[2])
                       (^speed per cycle^)
                       ( ---------------- ^virtual mouse speed per cycle^ --------------- )
                       ( -------------------- ^virtual mouse speed per cycle with throttle multiplier^ -------------------- )
                       ( ----------------------------------------- ^actual mouse speed per cycle with throttle multiplier^ ---------------------------------------- )

[1] "throttle_multiplier_effect" is a bit tricky. We want no throttle to result in a 1x multiplier and full throttle
to result in a (max_throttle_multiplier) multiplier. The following is the way to achieve that:
throttle_effect = (actual_throttle * (throttle_multiplier - 1) / max_throttle) + 1
                = (actual_throttle * (throttle_multiplier - 1) + max_throttle) / max_throttle

[2] virtual_mouse_granularity_effect is a way for us to emulate more granular (and slower) speeds than the mouse report allows.
For example, let's say we want 5x the granularity (so a value of 15 in our virtual speed equals a 3 in actual speed,
a value of 7 virtual results in 1.4 actual). The way we do this is by tracking the cycle index (mod granularity)
and rounding up/down the proportional number of times to achieve the fraction we want.
virtual_mouse_granularity_effect = 1 / granularity_multiplier

// Full equation

                        [                    ( max_virtual_mouse_speed )   ( actual_throttle * (throttle_multiplier - 1) + max_controller_throttle )                   ]   (           1            )
Mouse speed per cycle = [ controller_speed * ( ----------------------- ) * ( --------------------------------------------------------------------- ) + mouse_cycle_idx ] * ( ---------------------- )
                        [                    (  max_controller_speed   )   (                     max_controller_throttle                           )                   ]   ( granularity_multiplier )
*/

// Fixed
const uint64_t max_controller_speed = 512;
const uint64_t max_controller_throttle = 1024;

// Configurable
const int32_t drift_deadzone = 64;
const uint64_t max_virtual_mouse_speed = 8; // Speed increases proprtional to this
const uint64_t throttle_multiplier = 8;
// This must be a power of 2
const uint64_t granularity_multiplier = 16; // Speed decreses proportional to this
/* To make mouse granular speed smoother, we increment by [ (granularity_multiplier - 1) / 2 ]
 * Consider the case with 8 granularity and virtual speed of 3. We would round up if mouse index is >= 5:
 *
 * Then we get the following with the different approaches (^ for round up, v for round down):
 * Increment by 1:                 01234567 (vvvvv^^^)
 * Increment by other (8-1)/2=3:   03614725 (vv^vv^v^)
 */
const int mouse_cycle_incrementer = (granularity_multiplier-1)/2; // Speed decreses proportional to this

int mouse_cycle_idx = 0;

int32_t get_mouse_speed(int32_t controller_speed, uint64_t controller_throttle) {
  if (controller_speed < drift_deadzone && controller_speed > -drift_deadzone) {
    return 0;
  }
  return (((controller_speed * max_virtual_mouse_speed * (controller_throttle * (throttle_multiplier - 1) + max_controller_throttle)) / (max_controller_speed * max_controller_throttle)) + mouse_cycle_idx) / granularity_multiplier;
}

bool pointing_device_task(void) {
  mouse_cycle_idx += mouse_cycle_incrementer;
  mouse_cycle_idx %= granularity_multiplier;

  report_mouse_t report = pointing_device_get_report();
  report.x = get_mouse_speed(gamepad.axis_x, gamepad.throttle);
  report.y = get_mouse_speed(gamepad.axis_y, gamepad.throttle);
  // report.h = get_mouse_speed(gamepad.axis_rx, gamepad.throttle);
  // report.v = get_mouse_speed(gamepad.axis_ry, gamepad.throttle);
  pointing_device_set_report(report);
  return pointing_device_send();
}
