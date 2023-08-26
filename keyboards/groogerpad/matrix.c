#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "uart.h"
#include "timer.h"
#include "print.h"


void matrix_init_custom(void) {
  uart_init(9600);
}

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

int print_times = 0;

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
  if (print_times >= 3) {
    return 0;
  }

  while (uart_available()) {
    int buflen = sizeof(nina_gamepad_t);
    char xboxBuffer[buflen];
    for (int i = 0; i < buflen; i++) {
      xboxBuffer[i] = uart_read();
    }
    print_times++;
    nina_gamepad_t *gamepad = (nina_gamepad_t *)xboxBuffer;
    // send_byte((uint8_t)gamepad->buttons);
    // send_byte((uint8_t)(gamepad->buttons/256));
  }

  return 0;
}

/*
Example data:
00180000000d00000000000000140000000000000000000000000000
001800000015000000f6ffffff260000000000000000000000000000
001200000012000000f6ffffff2600000000000000000000000b0000
PAST0b00PAST0200PAST0000

*/
