// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../users/leep-frog/v2/leep_index_v2.h"

/**********
 * Layers *
 **********/

enum layers {
  LR_BASE,
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
    [TDK_COPY] = LEEP_TD_CLICK_KC_HOLD_FN(CK_COPY, LeepTD_url_copy_fn, LEEP_TD_NOVAL()),
    // Paste dance
    [TDK_PASTE] = LEEP_TD_CLICK_KC_HOLD_FN(CK_PASTE, LeepTD_url_paste_fn, LEEP_TD_NOVAL()),
};

#define TK_COPY TD(TDK_COPY)
#define TK_PSTE TD(TDK_PASTE)


/*********************
 * Main process loop *
 *********************/

enum custom_keycodes {
  ALT_TAB,
  SHIFT_ALT_TAB,
};

custom_keycode_fn_t custom_keycode_handlers[] = {
  [ALT_TAB] = &AltTabHandler,
  [SHIFT_ALT_TAB] = &AltShiftTabHandler,
};

#define CK_ATAB CK(ALT_TAB)
#define CK_STAB CK(SHIFT_ALT_TAB)

uint16_t Alt_keycodes[] = {
  CK_ATAB,
  CK_STAB,
  KC_BTN1,
};

/*********************
 * Main process loop *
 *********************/

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (Alt_block_processing(keycode)) {
    return false;
  }

  if (!process_custom_keycodes(keycode, record)) {
    return false;
  }

  return true;
}

/***********
 * Keymaps *
 ***********/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LAYOUT_xbox(
                C(G(KC_LEFT)),                               C(G(KC_RIGHT)),
                                  KC_H,                      KC_Y,
                TK_COPY, QK_BOOT,          S(KC_S), KC_X,             KC_B,
                CK_STAB,                                       KC_BTN1,
       CK_TABB,          CK_TABF,                              TK_PSTE,
                CK_ATAB
    )
};
