// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /************************************************************************************
     *  |                                       |                                       |
     *  |             LEFT FOOT                 |             RIGHT FOOT                |
     *  |                                       |                                       |
     *  |********************************************************************************|
     *  |                                       |                                       |
     *  | LEFT_TAP,    MIDDLE_TAP, RIGHT_TAP,   |  LEFT_TAP,   MIDDLE_TAP, RIGHT_TAP    |
     *  | LEFT_SLIDE,              RIGHT_SLIDE, |  LEFT_SLIDE,             RIGHT_SLIDE  |
     *  |                                       |                                       |
     *  | LF_HEEL_TAP, HEEL_TAP, RT_HEEL_TAP    | LF_HEEL_TAP, HEEL_TAP, RT_HEEL_TAP    |
     *  |                                       |                                       |
     *  |*******************************************************************************|
     */
    [0] = LAYOUT_pedals(
        KC_1,    KC_2,    KC_3,   /* <--- Left Pedal       */ KC_A,    KC_B,    KC_C,
        KC_4,             KC_5,   /*                       */ KC_D,             KC_E,
                                  /*                       */
        KC_6,    KC_7,    KC_8,   /*      Right Pedal ---> */ KC_F,    KC_G,    KC_H
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  return true;
}
