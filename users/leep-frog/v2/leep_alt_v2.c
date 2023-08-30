#pragma once

bool leep_alt_pressed = false;

bool Alt_is_active(void) {
    return leep_alt_pressed;
}

void Alt_activate(void) {
    leep_alt_pressed = true;
    register_code16(KC_RALT);
}

void Alt_deactivate(void) {
    leep_alt_pressed = false;
    unregister_code16(KC_RALT);
}
