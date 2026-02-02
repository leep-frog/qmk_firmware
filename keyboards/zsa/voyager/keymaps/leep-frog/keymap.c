#include QMK_KEYBOARD_H
#include "version.h"

#include "users/leep-frog/v2/leep_index_v2.h"

#include "users/leep-frog/keyboard-main/leep_index_kb.h"
#include "users/leep-frog/main.h"


// Can't evaluate macro in macro, so use this to ignore bottom row of keyboard
// https://stackoverflow.com/questions/35114050/is-there-a-way-to-force-c-preprocessor-to-evaluate-macro-arguments-before-the-ma
// #define LAYOUT(...) LAYOUT_moonlander(__VA_ARGS__)
// #define BOTTOM_ROW      KC_LCTL, KC_LALT, CK_MUT, CK_MUTS, KC_LCTL, CK_MCR1, CK_MCR2, KC_RCTL, KC_RALT, CK_EYE, KB_OFF, CK_LOCK


// TODO: Make top row special row, or shift everything up and make bottom row special row (better for thumb layer too
#define LEEP_LAYOUT(PFX) LAYOUT( \
    PFX##_TAB,       PFX##_Q, PFX##_W, PFX##_E, PFX##_R, PFX##_T,                      PFX##_Y, PFX##_U, PFX##_I,  PFX##_O,  PFX##_P,  PFX##_LBRC, \
    PFX##_CAPS_LOCK, PFX##_A, PFX##_S, PFX##_D, PFX##_F, PFX##_G,                      PFX##_H, PFX##_J, PFX##_K,  PFX##_L,  PFX##_SC, PFX##_QUOTE, \
    PFX##_LSFT,      PFX##_Z, PFX##_X, PFX##_C, PFX##_V, PFX##_B,                      PFX##_N, PFX##_M, PFX##_LT, PFX##_GT, PFX##_SL, PFX##_RSFT, \
    PFX##_ESC,       PFX##_1, PFX##_2, PFX##_3, PFX##_4, PFX##_5,                      PFX##_6, PFX##_7, PFX##_8,  PFX##_9,  PFX##_0,  PFX##_MINUS, \
            PFX##_LEFT_THUMB_PRIMARY, PFX##_LEFT_THUMB_SECONDARY,                      PFX##_RIGHT_THUMB_SECONDARY,  PFX##_RIGHT_THUMB_PRIMARY )
            // PFX##_LEFT_THUMB_SECONDARY, PFX##_LEFT_THUMB_PRIMARY,                      PFX##_RIGHT_THUMB_PRIMARY,  PFX##_RIGHT_THUMB_SECONDARY )




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [LR_BASE] = LAYOUT(
    //     CK_LOCK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
    //     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         TD_Y,    TD_U,    TD_I,    KC_O,    KC_P,    KC_VOLD,
    //     SC_LSPO, KC_A,    TD_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    TO_OTLK, SC_RSPC,
    //     KC_LCBR, KC_Z,    KC_X,    TD_C,    TD_V,    TD_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCBR,
    //                                         TO_SYMB, CK_SHFT,                      TO_CTRL,  TO_ALT
    // ),

    [LR_BASE] = LEEP_LAYOUT(LK_BASE),
    [LR_ELLA] = LEEP_LAYOUT(LK_ELLA),
    [LR_SYMB] = LEEP_LAYOUT(LK_SYMB),
    [LR_CTRL] = LEEP_LAYOUT(LK_CTRL),
    [LR_ALT] = LEEP_LAYOUT(LK_ALT),
    [LR_CTRL_X] = LEEP_LAYOUT(LK_CTRL_X),
    // [LR_CTRL_ALT] = LEEP_LAYOUT(LK_CTRL_ALT),
    [LR_CTRL_SHIFT] = LEEP_LAYOUT(LK_CTRL_SHIFT),
    [LR_SHORTCUTS] = LEEP_LAYOUT(LK_SHORTCUTS),
    [LR_OUTLOOK] = LEEP_LAYOUT(LK_OUTLOOK),
    [LR_ONE_HAND] = LEEP_LAYOUT(LK_ONE_HAND),
    [LR_SCROLL] = LEEP_LAYOUT(LK_SCROLL),

};
