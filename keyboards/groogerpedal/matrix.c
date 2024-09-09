#include QMK_KEYBOARD_H
#include "quantum.h"
#include "matrix.h"
#include "debug.h"
#include "timer.h"
#include "print.h"


// Max is 1023
const int blink_time = 125;

// void led_on(void) {
//   writePinHigh(??);
// }

// void led_off(void) {
//   writePinLow(??);
// }

// void led_blink(int times) {
//   for (int i = 0; i < times; i++) {
//     led_on();
//     wait_ms(blink_time);
//     led_off();
//     wait_ms(blink_time);
//   }
// }

void matrix_init_custom(void) {
  xprintf("Initializing groog controller");
  xprintf("Initing");
  setPinInput(D4);
}

uint8_t lpcount = 0;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;
  bool pressed = readPin(D4);
  if ((!!(current_matrix[0] & 1)) != (pressed)) {
    current_matrix[0] ^= 1;
    changed = true;
  }
  if (lpcount <= 3) {
    SEND_STRING("A");
    lpcount++;
    wait_ms(250);
  }

  return changed;
}

uint8_t llpcount = 0;

// bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
//   if (llpcount <= 3) {
//     SEND_STRING("B");
//     llpcount++;
//     wait_ms(250);
//   }

//   return false;
// }
