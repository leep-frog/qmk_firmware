// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "quantum/leep/custom_keycode_handler.h"

#include "users/leep-frog/v2/leep_aliases_v2.h"
#include "users/leep-frog/v2/leep_alt_v2.h"
#include "users/leep-frog/v2/leep_custom_keycodes_v2.h"
#include "users/leep-frog/v2/leep_workspace_v2.h"
#include "users/leep-frog/v2/leep_tap_dance_v2.h"

enum layers {
  LR_BASE,
  LR_COMBOS,
  LR_BROWSER_SHORTCUTS,
  LR_SHIFT,
};

enum custom_keycode_handlers {
  ALT_TAB_HANDLER,
  SHIFT_ALT_TAB_HANDLER,
  CK_WS_TWO,
  CK_WS_THREE,
};

custom_keycode_handler_t custom_keycode_handlers[] = {
  [ALT_TAB_HANDLER] = CK_HANDLER_FN(AltTabHandler),
  [SHIFT_ALT_TAB_HANDLER] = CK_HANDLER_FN(AltShiftTabHandler),
  [CK_WS_TWO] = CK_HANDLER_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT)))),
  [CK_WS_THREE] = CK_HANDLER_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_RIGHT)))),
};

#define CK_ATAB CK(ALT_TAB_HANDLER)
#define CK_STAB CK(SHIFT_ALT_TAB_HANDLER)

/**********
* Combos *
**********/

enum combos {
  COMBO_X,
  COMBO_Z,
};
// uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM x_combo[] = {KC_1, KC_B, COMBO_END};
const uint16_t PROGMEM z_combo[] = {KC_6, KC_G, COMBO_END};

combo_t key_combos[2] = {
  [COMBO_X] = COMBO(x_combo, KC_X),
  [COMBO_Z] = COMBO(z_combo, KC_Z),
  // [JSPACE_OH_RIGHT] = COMBO_ACTION(jspace_combo),
};

/*************
* Tap dances *
**************/
enum leep_tap_dances {
  TDK_TO_SHIFT = 0,
  TDK_TO_BROWSER,
  TDK_BROWSER_1,
  TDK_BROWSER_2,
  TDK_BROWSER_3,
  TDK_TO_SHORTCUTS,
};

tap_dance_action_t tap_dance_actions[] = {
  [TDK_TO_SHIFT] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_ENTER, LR_SHIFT),
  [TDK_TO_BROWSER] = LEEP_TD_CLICK_KC_HOLD_LAYER(WS_RIGHT, LR_BROWSER_SHORTCUTS),
  [TDK_BROWSER_1] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_CLOSE, CK_WWWB),
  [TDK_BROWSER_2] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_NEW, RCTL(KC_R)),
  [TDK_BROWSER_3] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_REOPEN, CK_WWWF),
  [TDK_TO_SHORTCUTS] = LEEP_TD_CLICK_KC_HOLD_LAYER(CK_TABF, LR_BROWSER_SHORTCUTS),
};

#define CK_ENTR_SHFT TD(TDK_TO_SHIFT)

#define WS_RGHT_BRWSR TD(TDK_TO_BROWSER)
#define CK_WWW_CLOSE_BACK TD(TDK_BROWSER_1)
#define CK_WWW_NEW_RELOAD TD(TDK_BROWSER_2)
#define CK_WWW_REOPEN_FORWARD TD(TDK_BROWSER_3)

#define CK_TABF_SHORTCUTS TD(TDK_TO_SHORTCUTS)

uint16_t Alt_keycodes[] = {
  CK_ATAB,
  CK_STAB,
  CK_ENTR_SHFT,
};

/*************
* Main logic *
**************/

#define LR_ELLA LR_BASE // Needed for below include

#include "users/leep-frog/v2/leep_index_v2.c"

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
    [LR_BASE] = LAYOUT_pedals(

                KC_8,            /*    Forward front tap  */           KC_I,
                KC_9,            /*    Slide to front     */           KC_J,
                KC_T,            /*    Forward heel tap   */           KC_K,

        KC_0,    KC_1,    KC_2,   /* <--- Left Pedal       */ KC_A,    KC_B,    KC_C,
        KC_3,             KC_4,   /*                       */ KC_D,             KC_E,
                                  /*                       */
        KC_5,    KC_6,    KC_7,   /*      Right Pedal ---> */ KC_F,    KC_Y,    KC_H
    ),

    // Layer used to define combos
    [LR_COMBOS] = LAYOUT_pedals(

                KC_8,            /*    Forward front tap  */           KC_I,
                KC_9,            /*    Slide to front     */           KC_J,
                KC_T,            /*    Forward heel tap   */           KC_K,

        KC_0,    KC_1,    KC_2,   /* <--- Left Pedal       */ KC_A,    KC_B,    KC_C,
        KC_3,             KC_4,   /*                       */ KC_D,             KC_E,
                                  /*                       */
        KC_5,    KC_6,    KC_7,   /*      Right Pedal ---> */ KC_F,    KC_G,    KC_H
    ),

    // [LR_BASE] = LAYOUT_pedals(
    //     CK_TABB, CK_TABF_SHORTCUTS, CK_ATAB, /**/ WS_LEFT, WS_RGHT_BRWSR, CK_ENTR_SHFT
    // ),

    // // Left is browser, right is shortcuts
    // [LR_BROWSER_SHORTCUTS] = LAYOUT_pedals(
    //     CK_WWW_CLOSE_BACK, CK_WWW_REOPEN_FORWARD, /**/ CK_WWW_NEW_RELOAD, CK_COPY, CK_PASTE, KC_PRINT_SCREEN
    // ),

    // [LR_SHIFT] = LAYOUT_pedals(
    //     CK_MTBB, CK_MTBF, CK_STAB, /**/ _______, _______, _______
    // ),
};


// TODO: Have pedal-holds activate modifiers for use by keyboard (shift, ctrl, etc.)
// TODO: Scroll layer?
// TODO: outlook?

// TODO: Should this just complement the mouse? (i.e. have them be disjoint sets of actions?)
// To find out, see how often we use this while hands are free or at the keyboard

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // if (AltBlockProcessing(keycode, record)) {
  //   return false;
  // }

  if (!process_custom_keycodes(keycode, record)) {
    return false;
  }

  return true;
}
