// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Roughly the shape of an xbox controller
    [0] = LAYOUT_xbox(
                _______,                                              _______,
                C(G(KC_LEFT)),                                        C(G(KC_RIGHT)),
                                           _______,                   KC_Y,
                C(KC_C),          KC_BTN2,          KC_BTN2, KC_X,             KC_B,
                CK_UP,                     _______,                   KC_A,
       KC_LEFT,          CK_RGHT,                   C(V),
                CK_DOWN
    )
};
