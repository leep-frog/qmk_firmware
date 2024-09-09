// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_pedals(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  return true;
}
