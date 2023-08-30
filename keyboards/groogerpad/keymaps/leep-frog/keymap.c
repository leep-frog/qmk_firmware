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
  TDK_LEFT_DPAD,
  TDK_RIGHT_DPAD,
  TDK_SELECT,
  TDK_START,
};

tap_dance_action_t tap_dance_actions[] = {
  // Include comments for line separation when formatting.
  // Copy dance
  [TDK_COPY] = LEEP_TD_CLICK_KC_HOLD_FN(CK_COPY, LeepTD_url_copy_fn, LEEP_TD_NOVAL()),
  // Paste dance
  [TDK_PASTE] = LEEP_TD_CLICK_KC_HOLD_FN(CK_PASTE, LeepTD_url_paste_fn, LEEP_TD_NOVAL()),
  // Left DPAD dance
  [TDK_LEFT_DPAD] = LEEP_TD_CLICK_KC_HOLD_KC(CK_TABB, CK_WWWB),
  // Right DPAD dance
  [TDK_RIGHT_DPAD] = LEEP_TD_CLICK_KC_HOLD_KC(CK_TABF, CK_WWWF),
  // Select dance TODO: QK_BOOT fix?
  [TDK_SELECT] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_CLOSE, QK_BOOT),
  // Start dance
  [TDK_START] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_NEW, CK_WWW_REOPEN),
};

#define TK_COPY TD(TDK_COPY)
#define TK_PSTE TD(TDK_PASTE)
#define TK_LEFT TD(TDK_LEFT_DPAD)
#define TK_RGHT TD(TDK_RIGHT_DPAD)
#define TK_SLCT TD(TDK_SELECT)
#define TK_STRT TD(TDK_START)

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
                TK_COPY, TK_SLCT,          TK_STRT, KC_X,             KC_B,
                CK_STAB,                                     KC_BTN1,
       TK_LEFT,          TK_RGHT,                            TK_PSTE,
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
