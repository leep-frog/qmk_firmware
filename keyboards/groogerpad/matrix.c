#include QMK_KEYBOARD_H
#include "matrix.h"
#include "timer.h"

void matrix_init_custom(void) {
    // TODO: initialize hardware here
}

uint32_t groog_time = 0;
int pressed = 0;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (pressed > 0) {
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
    // TODO: add matrix scanning routine here

    return false;
}
