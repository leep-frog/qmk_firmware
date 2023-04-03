// To ctrl layer functions
static uint16_t ctrl_timer;
static bool     ctrl_interrupted = false;

void ToCtrl_handled(uint16_t keycode) {
    if (keycode != TO_CTRL) {
        ctrl_interrupted = true;
    }
}

void ToCtrl_run(bool pressed) {
    if (pressed) {
        ctrl_interrupted = false;
        ctrl_timer       = timer_read();
        layer_on(LR_CTRL);
    } else {
        layer_off(LR_CTRL);
        if (!ctrl_interrupted && timer_elapsed(ctrl_timer) < TAPPING_TERM) {
            tap_code16(KC_TAB);
        }
    }
}
