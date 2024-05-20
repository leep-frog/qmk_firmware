#pragma once

bool leep_alt_pressed = false;

bool alt_is_active(void) {
    return leep_alt_pressed;
}

void activate_alt(void) {
    leep_alt_pressed = true;
    register_code16(KC_RALT);
}

void deactivate_alt(void) {
    leep_alt_pressed = false;
    unregister_code16(KC_RALT);
}
