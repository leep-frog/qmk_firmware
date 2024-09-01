#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "timer.h"
#include "print.h"


// Max is 1023
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
  xprintf("Initializing groog controller");
  xprintf("Initing");
  // setPinInput(D4);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;
  return changed;
}
