// To ctrl layer functions
static uint16_t ctrl_timer;
static bool     ctrl_interrupted = false;

void ToCtrl_handled(uint16_t keycode) {
    if (keycode != ToCtrlKeycode) {
        ctrl_interrupted = true;
    }
}

bool ToCtrl_run(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        ctrl_interrupted = false;
        ctrl_timer       = timer_read();
        layer_on(CtrlLayer);
    } else {
        layer_off(CtrlLayer);
        if (!ctrl_interrupted && timer_elapsed(ctrl_timer) < TAPPING_TERM) {
            tap_code16(KC_TAB);
        }
    }
    return false;
}
