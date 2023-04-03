// To alt layer functions
static uint16_t alt_timer;
static bool     alt_interrupted = false;

void ToAlt_handled(uint16_t keycode) {
    if (keycode != TO_ALT) {
        alt_interrupted = true;
    }
}

void ToAlt_run(bool pressed) {
    if (pressed) {
        alt_interrupted = false;
        alt_timer       = timer_read();
        layer_on(LR_ALT);
    } else {
        layer_off(LR_ALT);
        if (!alt_interrupted && timer_elapsed(alt_timer) < TAPPING_TERM) {
            tap_code16(KC_ENTER);
        }
    }
}
