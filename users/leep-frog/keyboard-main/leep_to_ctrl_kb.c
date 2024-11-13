#include "timer.h"

// To ctrl layer functions
static uint16_t ctrl_timer;
static bool     ctrl_interrupted = false;
static bool     ctrl_press_mode = false;
static uint32_t ctrl_last_unpress = 0;

void ToCtrl_handled(uint16_t keycode) {
    if (keycode != ToCtrlKeycode) {
        ctrl_interrupted = true;
    }
}

// TODO: Eliminate chance of accidental enter by setting value in matrix scan
// use similar concept to ToCtrl_handled, but ToCtrl_scan and put in scan code in main.c
// TODO: Add test? Eh maybe not

bool ToCtrl_run(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
      if (timer_elapsed32(ctrl_last_unpress) < TAPPING_TERM) {
        ctrl_press_mode = true;
        register_code16(KC_ENTER);
      } else {
        ctrl_interrupted = false;
        ctrl_timer       = timer_read();
        layer_on(CtrlLayer);
      }
      return false;
    }


    // Unpress
    ctrl_last_unpress = timer_read32();
    if (ctrl_press_mode) {
      ctrl_press_mode = false;
      unregister_code16(KC_ENTER);
    } else {
      layer_off(CtrlLayer);
      if (!ctrl_interrupted && timer_elapsed(ctrl_timer) < TAPPING_TERM) {
        ctrl_last_unpress = timer_read32();
        tap_code16(KC_ENTER);
      }
    }
    return false;
}
