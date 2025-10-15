#include QMK_KEYBOARD_H
#include "version.h"

#include "users/leep-frog/v2/leep_index_v2.h"

#include "users/leep-frog/keyboard-main/leep_index_kb.h"
#include "users/leep-frog/main.h"

// Can't evaluate macro in macro, so use this to ignore bottom row of keyboard
// https://stackoverflow.com/questions/35114050/is-there-a-way-to-force-c-preprocessor-to-evaluate-macro-arguments-before-the-ma
#define ML_LAYOUT(...) LAYOUT_moonlander(__VA_ARGS__)
#define BOTTOM_ROW      KC_LCTL, KC_LALT, CK_MUT, CK_MUTS, KC_LCTL, CK_MCR1, CK_MCR2, KC_RCTL, KC_RALT, CK_EYE, KB_OFF, CK_LOCK

#define LEEP_LAYOUT(PFX, top_left, top_right, top_right_right, middle_left, middle_right, middle_right_right, bottom_left, bottom_right) ML_LAYOUT( \
    PFX##_ESC,   PFX##_1, PFX##_2, PFX##_3, PFX##_4, PFX##_5, top_left,       top_right,  PFX##_6, PFX##_7, PFX##_8,    PFX##_9,   PFX##_0,    top_right_right, \
    PFX##_TAB,   PFX##_Q, PFX##_W, PFX##_E, PFX##_R, PFX##_T, middle_left,       middle_right, PFX##_Y, PFX##_U, PFX##_I,    PFX##_O,   PFX##_P,    middle_right_right, \
PFX##_CAPS_LOCK, PFX##_A, PFX##_S, PFX##_D, PFX##_F, PFX##_G, bottom_left,       bottom_right, PFX##_H, PFX##_J, PFX##_K,    PFX##_L,   PFX##_SC, PFX##_QUOTE, \
    PFX##_LSFT, PFX##_Z, PFX##_X, PFX##_C, PFX##_V, PFX##_B,                         PFX##_N, PFX##_M, PFX##_LT, PFX##_GT, PFX##_SL, PFX##_RSFT, \
                                                 BOTTOM_ROW, \
                          PFX##_LEFT_THUMB_PRIMARY, PFX##_LEFT_THUMB_SECONDARY, PFX##_LEFT_THUMB_TERTIARY, PFX##_RIGHT_THUMB_TERTIARY, PFX##_RIGHT_THUMB_SECONDARY, PFX##_RIGHT_THUMB_PRIMARY)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LEEP_LAYOUT(LK_BASE,
        WS_LEFT, KC_ESC,  KC_VOLU,
        LGHT_ON, LGHT_OF, KC_VOLD,
        WS_LEFT, CK_MCR1
    ),

    [LR_ELLA] = LEEP_LAYOUT(LK_ELLA,
        KC_NO, KC_NO, _______,
        KC_NO, KC_NO, KC_BSLS,
        KC_NO, KC_NO
    ),

    [LR_CTRL] = LEEP_LAYOUT(LK_CTRL,
        RCTL(WS_LEFT), KC_ESC, _______,
        KC_LEFT,       KC_RGHT, CL(BSLS),
        _______,        _______
    ),

    [LR_CTRL_X] = LEEP_LAYOUT(LK_CTRL_X,
        RCTL(WS_LEFT), RCTL(KC_ESC),  _______,
        KC_LEFT,       KC_RIGHT,      CL(BSLS),
        RCTL(WS_LEFT), RCTL(WS_RGHT)
    ),

    [LR_ALT] = LEEP_LAYOUT(LK_ALT,
        RALT(WS_LEFT),  RALT(KC_ESC),  _______,
        KC_LEFT,        KC_RIGHT,      AL(BSLS),
        RALT(WS_LEFT),  RALT(WS_RGHT)
    ),

    [LR_CTRL_SHIFT] = LEEP_LAYOUT(LK_CTRL_SHIFT,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______
    ),

    // This layer is basically identical to the safe layer aside from the thumb keys.
    [LR_CTRL_ALT] = ML_LAYOUT(
        CK_LOCK, KC_1, KC_2, KC_3, KC_4, KC_5, _______,       KC_ESC,  KC_6, KC_7, KC_8,    KC_9,   KC_0,    _______,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, LGHT_ON,       LGHT_OF, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_LPRN, KC_A, KC_S, KC_D, KC_F, KC_G, WS_LEFT,       WS_RGHT, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_RPRN,
        KC_LCBR, KC_Z, KC_X, KC_C, KC_V, KC_B,                         KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCBR,

                                                      BOTTOM_ROW,

                             KC_RSFT, KC_TAB, _______,        KC_RGUI, KC_ENTER, KC_SPACE
    ),

   [LR_SHORTCUTS] = ML_LAYOUT(
        _______,  _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, KC_ENT,  _______, _______, _______,           _______, KC_WH_U, URL_CPY, KC_MS_U, _______, _______, _______,
        KC_ENTER, _______, KC_BSPC, KC_DEL,  _______, _______, _______,           _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_RCTL, _______,
        _______,  _______, _______, _______, _______, GD_BULT,                             CK_NEW,  GD_HD_1, GD_HD_2, GD_HD_3, _______, _______,

                                                                     BOTTOM_ROW,

                                           _______, _______, _______,             _______, _______, _______
    ),

    [LR_SYMB] = LEEP_LAYOUT(LK_SYMB,
        _______, _______, _______,
        _______, _______, KC_F12,
        _______, _______
    ),

    [LR_OUTLOOK] = LEEP_LAYOUT(LK_OUTLOOK,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______
    ),

    [LR_ONE_HAND] = LEEP_LAYOUT(LK_ONE_HAND,
        _______, _______, _______,
        _______, _______, KC_TAB,
        _______, _______
    ),

    [LR_SCROLL] = LEEP_LAYOUT(LK_SCROLL,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______
    ),

    /*
    [EMPTY_LAYER] = ML_LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,

                                                                      BOTTOM_ROW,

                                            _______, _______, _______,           _______, _______, _______
    ),
    */
};
