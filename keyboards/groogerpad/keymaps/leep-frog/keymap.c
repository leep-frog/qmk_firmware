// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../users/leep-frog/v2/leep_index_v2.h"

/**********
 * Layers *
 **********/

enum layers {
  LR_BASE,
  LR_ALT,
};

const uint16_t AltLayer = LR_ALT;

void keyboard_post_init_user(void) {
  SET_LAYER_HANDLER(LR_ALT, AltLayerHandler);
}

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

bool AltBButtonHandler(keyrecord_t* record) {
  if (record->event.pressed) {
    register_code16(KC_ESCAPE);
    wait_ms(100);
    layer_off(LR_ALT);
  } else {
    unregister_code16(KC_ESCAPE);
  }

  return false;
}

enum custom_keycodes {
  ALT_TAB,
  SHIFT_ALT_TAB,
  LR_ALT_B_BUTTON,
};

custom_keycode_fn_t custom_keycode_handlers[] = {
  [ALT_TAB] = &AltTabHandler,
  [SHIFT_ALT_TAB] = &AltShiftTabHandler,
  [LR_ALT_B_BUTTON] = &AltBButtonHandler,
};

#define CK_ALTB CK(LR_ALT_B_BUTTON)
#define CK_ATAB CK(ALT_TAB)
#define CK_STAB CK(SHIFT_ALT_TAB)

uint16_t Alt_keycodes[] = {
  CK_ATAB,
  CK_STAB,
  CK_ALTB,
};

/*********************
 * Main process loop *
 *********************/

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (AltBlockProcessing(keycode, record)) {
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
                CK_STAB,                                     KC_BTN1,
       CK_TABB,          CK_TABF,                            TK_PSTE,
                CK_ATAB
    ),

    [LR_ALT] = LAYOUT_xbox(
                _______,                                     _______,
                                  _______,                   _______,
                _______, _______,          _______, _______,          CK_ALTB,
                CK_STAB,                                     _______,
       _______,          _______,                            _______,
                CK_ATAB
    ),
};
