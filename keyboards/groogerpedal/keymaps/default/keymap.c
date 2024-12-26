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

                KC_8,            /*    Forward front tap  */          KC_I,
                KC_9,            /*    Slide to front     */          KC_J,
                KC_T,            /*    Forward heel tap   */          KC_K,

        KC_0,    KC_1,    KC_2,   /* <--- Left Pedal       */ KC_A,    KC_B,    KC_C,
        KC_3,             KC_4,   /*                       */ KC_D,             KC_E,
                                  /*                       */
        KC_5,    KC_6,    KC_7,   /*      Right Pedal ---> */ KC_F,    KC_G,    KC_H
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  return true;
}
