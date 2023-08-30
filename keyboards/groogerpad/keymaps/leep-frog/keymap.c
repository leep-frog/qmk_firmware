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
  LR_OUTLOOK,
  LR_TYPE,
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
  TDK_LB,
  TDK_RB,
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
  // LB dance
  [TDK_LB] = LEEP_TD_CLICK_KC_HOLD_LAYER(WS_LEFT, LR_TYPE),
  // RB dance
  [TDK_RB] = LEEP_TD_CLICK_KC_HOLD_LAYER(WS_RIGHT, LR_OUTLOOK),
};

#define TK_COPY TD(TDK_COPY)
#define TK_PSTE TD(TDK_PASTE)
#define TK_LEFT TD(TDK_LEFT_DPAD)
#define TK_RGHT TD(TDK_RIGHT_DPAD)
#define TK_SLCT TD(TDK_SELECT)
#define TK_STRT TD(TDK_START)
#define TK_LB TD(TDK_LB)
#define TK_RB TD(TDK_RB)

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
  OUTLOOK_RELOAD,
};

custom_keycode_fn_t custom_keycode_handlers[] = {
  [ALT_TAB] = &AltTabHandler,
  [SHIFT_ALT_TAB] = &AltShiftTabHandler,
  [LR_ALT_B_BUTTON] = &AltBButtonHandler,
  [OUTLOOK_RELOAD] = &OutlookTodayHandler,
};

#define CK_ALTB CK(LR_ALT_B_BUTTON)
#define CK_ATAB CK(ALT_TAB)
#define CK_STAB CK(SHIFT_ALT_TAB)
#define CK_OLRL CK(OUTLOOK_RELOAD)

uint16_t Alt_keycodes[] = {
  CK_ATAB,
  CK_STAB,
  CK_ALTB,
};

/*********************
 * Main process loop *
 *********************/

bool joystick_mouse_enabled(void) { return get_highest_layer(layer_state) == 0; }
bool joystick_scroll_enabled(void) { return get_highest_layer(layer_state) == 0; }

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
                TK_LB,                                                TK_RB,
                                           KC_H,                      KC_TAB,
                TK_COPY,          TK_SLCT,          TK_STRT, SH(TAB),          KC_BTN2,
                CK_STAB,                                              KC_BTN1,
       TK_LEFT,          TK_RGHT,                   TK_PSTE,
                CK_ATAB
    ),

    [LR_ALT] = LAYOUT_xbox(
                _______,                                              _______,
                                           _______,                   _______,
                _______,          _______,          _______, _______,          CK_ALTB,
                CK_STAB,                                              _______,
       _______,          _______,                   _______,
                CK_ATAB
    ),

    [LR_OUTLOOK] = LAYOUT_xbox(
                _______,                                              _______,
                                           _______,                   OL_PREV,
                _______,          _______,          CK_OLRL, OL_DEL,           _______,
                _______,                                              OL_NEXT,
       _______,          _______,                   _______,
                GU(TAB)
    ),

    [LR_TYPE] = LAYOUT_xbox(
                _______,                                              _______,
                                           _______,                   KC_DEL,
                _______,          KC_ESC,           KC_ENT,  KC_BSPC,          KC_END,
                KC_UP,                                                KC_HOME,
       KC_LEFT,          KC_RIGHT,                  _______,
                KC_DOWN
    ),

    /*[LR_TYPE_2] = LAYOUT_xbox(
                _______,                                              _______,
                                           _______,                   CL(DEL),
                _______,          _______,          _______, CL(BSPC),         KC_END,
                _______,                                              _______,
       CL(LEFT),         CL(RIGHT),                 _______,
                _______
    ),*/
};
