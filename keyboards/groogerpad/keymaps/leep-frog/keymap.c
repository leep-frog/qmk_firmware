// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../users/leep-frog/v2/leep_index_v2.c"

enum LAYERS {
  LR_BASE,
  NUM_LAYERS,
};

/**********
 * Layers *
 **********/

layer_change_fn_t layer_handlers[] = {
  [0 ... NUM_LAYERS - 1] = NULL,
};

/**************
 * Tap Dances *
 **************/

enum leep_tap_dances {
  TDK_COPY = 0,
  TDK_PASTE,
};

tap_dance_action_t tap_dance_actions[] = {
    // Copy dance
    [TDK_COPY] = LEEP_TD_CLICK_KC_HOLD_KC(CK_COPY, KC_C),
    // Paste dance
    [TDK_PASTE] = LEEP_TD_CLICK_KC_HOLD_KC(CK_PASTE, KC_P),
};

#define TK_COPY TD(TDK_COPY)
#define TK_PSTE TD(TDK_PASTE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LAYOUT_xbox(
                C(G(KC_LEFT)),                               C(G(KC_RIGHT)),
                                  KC_H,                      KC_Y,
                TK_COPY, QK_BOOT,          S(KC_S), KC_X,             KC_B,
                KC_UP,                                       KC_BTN1,
       KC_LEFT,          KC_RIGHT,                           TK_PSTE,
                KC_DOWN
    )
};
