// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keymap_introspection.h"

const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[] = {
  COMBO(test_combo1, KC_C),
};
enum custom_keycodes {
  BLOOP,
};
bool Bloop(keyrecord_t *record) { return false; }
custom_keycode_handler_t custom_keycode_handlers[] = {
  [BLOOP] = NULL,
};
uint16_t Alt_keycodes[] = {
  KC_Z,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Roughly the shape of an xbox controller
    [0] = LAYOUT_xbox(
                _______,                                              _______,
                C(G(KC_LEFT)),                                        C(G(KC_RIGHT)),
                                           _______,                   KC_Y,
                C(KC_C),          KC_BTN2,          KC_BTN2, KC_X,             KC_B,
                KC_UP,                     _______,                   KC_A,
       KC_LEFT,          KC_RGHT,                   C(KC_V),
                KC_DOWN
    )
};