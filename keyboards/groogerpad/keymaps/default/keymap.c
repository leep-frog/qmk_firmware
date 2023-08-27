// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     *
    [0] = LAYOUT_groogerpad(
        KC_7,   KC_8,   KC_9,   KC_A,
        KC_4,   KC_5,   KC_6,   KC_B,
        KC_1,   KC_2,   KC_3,   KC_C,
        KC_0,   KC_D, KC_E, KC_F
    )*/

    [0] = LAYOUT_xbox(
                KC_L,                               KC_R,
                S(KC_L),                            S(KC_R),
                                  KC_H,             KC_Y,
                KC_J,    KC_S,    S(KC_S), KC_X,             KC_B,
                KC_UP,                              KC_A,
       KC_LEFT,          KC_RIGHT,                  S(KC_J),
                KC_DOWN
    )
};
