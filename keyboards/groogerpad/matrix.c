#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "uart.h"
#include "timer.h"
#include "print.h"


void matrix_init_custom(void) {
  uart_init(9600);
  debug_enable=true;
  xprintf("groog matrix init\n");
}

uint32_t groog_time = 0;
int pressed = 0;

bool first_press = true;

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

  int32_t gyro[3];
  int32_t accel[3];
} nina_gamepad_t;

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
  xprintf("HELLO\n");
  if (first_press) {
    SEND_STRING("A");
    first_press = false;
  }

  while (uart_available()) {
    // SEND_STRING("R0");

    // Comes in 28 byte groups (size of nina_gamepad_t)
    // TODO: Use sizeof? Need to divide by anything?
    // int buflen = 28;
    // char xboxBuffer[buflen];
    // for (int i = 0; i < xboxBuffer; i++) {
      // xboxBuffer[i] = 0;
    // }
    // strcpy(dogBuf, message);

    // TODO: Do while available if we have more recent controller stuff?
    // SEND_STRING("R1");
    // for (int i = 0; i < 28; i++) {
      // xboxBuffer[i] = uart_read();
    // }
    // SEND_STRING("R2");
    // nina_gamepad_t *gamepad = (nina_gamepad_t *)xboxBuffer;
    // SEND_STRING("R3");
    send_byte(uart_read());
    // send_byte((uint8_t)gamepad->buttons);
    // SEND_STRING("R4");
    // send_byte((uint8_t)(gamepad->buttons / 256));
    // SEND_STRING("R5");
    // SEND_STRING("\n");
  }
    /*if (pressed > 0) {
      wait_ms(10);
      pressed--;
      if (pressed == 0) {
        current_matrix[0] = 0;
        return true;
      } else {
        return false;
      }
    }

    uint32_t new_time = timer_read32();
    if (TIMER_DIFF_32(timer_read32(), groog_time) > 2500) {
      SEND_STRING("YUP");
      current_matrix[0] = 3;
      pressed = 10;
      groog_time = new_time;
      return true;
    }
    // TODO: add matrix scanning routine here*/

    return 0;
}
