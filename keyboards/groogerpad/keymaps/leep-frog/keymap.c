// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LAYOUT_xbox(
                C(G(KC_LEFT)),                               C(G(KC_RIGHT)),
                                  KC_H,                      KC_Y,
                KC_J,    QK_BOOT,          S(KC_S), KC_X,             KC_B,
                KC_UP,                                       KC_BTN1,
       KC_LEFT,          KC_RIGHT,                           S(KC_J),
                KC_DOWN
    )
};
