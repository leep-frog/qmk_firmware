// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../users/leep-frog/v2/leep_index_v2.h"
#include "groogermouse.h"

/**********
 * Layers *
 **********/

enum layers {
  LR_BASE,
  LR_ALT,
  LR_OUTLOOK,
  LR_TYPE,
  LR_TYPE_2,
};

const uint16_t AltLayer = LR_ALT;

void keyboard_post_init_user(void) {
  SET_LAYER_HANDLER(LR_ALT, AltLayerHandler);
}

/****************
 * Word Buttons *
 ****************/

enum word_button_layers_t {
  word_layer_A,
  word_layer_B,
  word_layer_X,
  word_layer_Y,
  NUM_WORD_LAYERS,
};

bool word_buttons[NUM_WORD_LAYERS] = {
  [0 ... NUM_WORD_LAYERS - 1] = false,
};

const char words[NUM_WORD_LAYERS][9] = {
  // Order of chars is based on definition of joystick_direction_t (center, then clockwise starting from west)
  /* bs */"_zquickx",
  " _wtherop",
  "\n__blandv",
  /* del */"_jfgsym_",
};

void left_joystick_handler(enum joystick_direction_t direction) {
  if (get_highest_layer(layer_state) != LR_TYPE_2) {
    return;
  }
  for (int word_layer = 0; word_layer < NUM_WORD_LAYERS; word_layer++) {
    if (word_buttons[word_layer]) {
      // TODO: Shift
      send_char(words[word_layer][direction]);
    }
  }
}

#define WORD_HANDLER_DEFINE(word_layer) bool WordLayerHandler_##word_layer (keyrecord_t* record) { \
  word_buttons[word_layer] = record->event.pressed; \
  if (record->event.pressed) { \
    /* TODO: Shift */ \
    send_char(words[word_layer][left_joystick_direction]); \
  } \
  return false; \
}

WORD_HANDLER_DEFINE(0)
WORD_HANDLER_DEFINE(1)
WORD_HANDLER_DEFINE(2)
WORD_HANDLER_DEFINE(3)

#define WORD_HANDLER_FUNC(word_layer) &WordLayerHandler_##word_layer

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

/**********
 * Combos *
 **********/

const uint16_t PROGMEM test_combo1[] = {TK_LB, TK_RB, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, TG(LR_TYPE_2)),
    // COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

/*******************
 * Custom keycodes *
 *******************/

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
  CUSTOM_KEYCODE_END,
  WORD_LAYER_0,
  WORD_LAYER_1,
  WORD_LAYER_2,
  WORD_LAYER_3,
};

custom_keycode_fn_t custom_keycode_handlers[] = {
  [ALT_TAB] = &AltTabHandler,
  [SHIFT_ALT_TAB] = &AltShiftTabHandler,
  [LR_ALT_B_BUTTON] = &AltBButtonHandler,
  [OUTLOOK_RELOAD] = &OutlookTodayHandler,
  [WORD_LAYER_0] = WORD_HANDLER_FUNC(0),
  [WORD_LAYER_1] = WORD_HANDLER_FUNC(1),
  [WORD_LAYER_2] = WORD_HANDLER_FUNC(2),
  [WORD_LAYER_3] = WORD_HANDLER_FUNC(3),
};

#define CK_ALTB CK(LR_ALT_B_BUTTON)
#define CK_ATAB CK(ALT_TAB)
#define CK_STAB CK(SHIFT_ALT_TAB)
#define CK_OLRL CK(OUTLOOK_RELOAD)
#define CK_WL_0 CK(WORD_LAYER_0)
#define CK_WL_1 CK(WORD_LAYER_1)
#define CK_WL_2 CK(WORD_LAYER_2)
#define CK_WL_3 CK(WORD_LAYER_3)

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
                                           KC_H,                      SH(TAB),
                TK_COPY,          TK_SLCT,          TK_STRT, KC_TAB,           KC_BTN2,
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
                _______,                                         _______,
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

    [LR_TYPE_2] = LAYOUT_xbox(
                _______,                                              _______,
                                           _______,                   CK_WL_3,
                _______,          _______,          _______, CK_WL_1,             CK_WL_2,
                _______,                                              CK_WL_0,
       CL(LEFT),         CL(RIGHT),                 _______,
                _______
    ),
};
