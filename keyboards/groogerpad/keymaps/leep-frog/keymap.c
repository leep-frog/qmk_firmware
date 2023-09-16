// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../users/leep-frog/v2/leep_index_v2.h"
#include "groogermouse.h"
#include "uart.h"
#include "groogerpad.h"

/**********
 * Layers *
 **********/

enum layers {
  LR_BASE,
  LR_ALT,
  LR_OUTLOOK,
  LR_TYPE,
  LR_SETTINGS,
  LR_SYMB,
};

const uint16_t AltLayer = LR_ALT;

void TypeLayerHandler(bool activated) {
  if (activated) {
    writePinHigh(D4);
  } else {
    writePinLow(D4);
  }
}

void keyboard_post_init_user(void) {
  SET_LAYER_HANDLER(LR_TYPE, TypeLayerHandler);
}

/****************
 * Word Buttons *
 ****************/

enum word_button_layers_t {
  // Left joystick with buttons
  word_layer_A,
  word_layer_B,
  word_layer_X,
  word_layer_Y,
  word_layer_RB, // If add another left layer, be sure to update LAST_LEFT_LAYER below
  // Right joystick with dpad
  symb_layer_left,
  symb_layer_up,
  symb_layer_down,
  NUM_WORD_LAYERS,
};
#define LAST_LEFT_LAYER word_layer_RB

bool word_buttons[NUM_WORD_LAYERS] = {
  [0 ... NUM_WORD_LAYERS - 1] = false,
};

uint16_t word_layer_registered_codes[NUM_WORD_LAYERS] = {
  [0 ... NUM_WORD_LAYERS - 1] = 0,
};

const uint16_t words[NUM_WORD_LAYERS][9] = {
  // Order of chars is based on definition of joystick_direction_t (center, then clockwise starting from west)
/*{ CENTER,  WEST,    NW,      NORTH,   NE,      EAST,    SE,      SOUTH,   SW       } */
  // A button
  { KC_SPACE,KC_T,    KC_H,    KC_E,    KC_R,    KC_O,    KC_P,    KC_SLSH, KC_W },
  // B button
  { KC_ENTER,KC_B,    KC_L,    KC_A,    KC_N,    KC_D,    KC_V,    KC_DOT, KC_COMMA },
  // X button
  { KC_BSPC, KC_Q,    KC_U,    KC_I,    KC_C,    KC_K,    KC_X,    KC_BSLS, KC_Z },
  // Y button
  { KC_DEL,  KC_F,    KC_G,    KC_S,    KC_Y,    KC_M,    KC_SCLN, KC_QUOT, KC_J },
  // RB. Setup is the number pad (0 is click joystick)
  { KC_5,    KC_4,    KC_7,    KC_8,    KC_9,    KC_6,    KC_3,    KC_2,    KC_1 },

  { KC_LEFT, KC_GRV,  KC_QUOT, KC_DOT,  KC_COMM, KC_EQL,  KC_MINS, KC_SCLN, KC_SLSH },
  { KC_UP,   KC_DLR,  KC_HASH, KC_ASTR, KC_AT,   KC_AMPR, KC_CIRC, KC_PERC, KC_EXLM },
  { KC_DOWN, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_RCBR, KC_LCBR, KC_BSLS, KC_PIPE },
  /*                                            ^ Swap order for second half because left and right is reversed here */


};

void left_joystick_handler(enum joystick_direction_t direction) {
  if (get_highest_layer(layer_state) != LR_TYPE) {
    return;
  }
  for (int word_layer = 0; word_layer <= LAST_LEFT_LAYER; word_layer++) {
    if (word_buttons[word_layer]) {
      // Unregister key we are leaving from
      unregister_code16(word_layer_registered_codes[word_layer]);
      // Register key we are entering into
      register_code16(words[word_layer][direction]);
      word_layer_registered_codes[word_layer] = words[word_layer][direction];
    }
  }
}

void right_joystick_handler(enum joystick_direction_t direction) {
  if (get_highest_layer(layer_state) != LR_TYPE) {
    return;
  }
  for (int word_layer = LAST_LEFT_LAYER+1; word_layer < NUM_WORD_LAYERS; word_layer++) {
    if (word_buttons[word_layer]) {
      // Unregister key we are leaving from
      unregister_code16(word_layer_registered_codes[word_layer]);
      // Register key we are entering into
      register_code16(words[word_layer][direction]);
      word_layer_registered_codes[word_layer] = words[word_layer][direction];
    }
  }
}

#define WORD_HANDLER_DEFINE(word_layer, dir) \
bool WordLayerHandler_##word_layer (keyrecord_t* record, custom_keycode_value_t *_) { \
  word_buttons[word_layer] = record->event.pressed; \
  if (record->event.pressed) { \
    register_code16(words[word_layer][dir##_joystick_direction]); \
    word_layer_registered_codes[word_layer] = words[word_layer][dir##_joystick_direction]; \
  } else { \
    unregister_code16(word_layer_registered_codes[word_layer]); \
    word_layer_registered_codes[word_layer] = KC_NO; \
  } \
  return false; \
}

WORD_HANDLER_DEFINE(0, left)
WORD_HANDLER_DEFINE(1, left)
WORD_HANDLER_DEFINE(2, left)
WORD_HANDLER_DEFINE(3, left)
WORD_HANDLER_DEFINE(4, left)
WORD_HANDLER_DEFINE(5, right)
WORD_HANDLER_DEFINE(6, right)
WORD_HANDLER_DEFINE(7, right)

#define WORD_HANDLER_FUNC(word_layer) CK_HANDLER_FN(WordLayerHandler_##word_layer)

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
  // Select dance
  [TDK_SELECT] = LEEP_TD_CLICK_KC_HOLD_LAYER(CK_WWW_CLOSE, LR_SETTINGS),
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
    COMBO(test_combo1, TG(LR_TYPE)),
};

/*******************
 * Custom keycodes *
 *******************/

bool AltBButtonHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    register_code16(KC_ESCAPE);
    wait_ms(100);
    layer_off(LR_ALT);
  } else {
    unregister_code16(KC_ESCAPE);
  }

  return false;
}

enum custom_keycode_handlers {
  ALT_TAB_HANDLER,
  SHIFT_ALT_TAB_HANDLER,
  LR_ALT_B_BUTTON_HANDLER,
  OUTLOOK_RELOAD_HANDLER,
  CUSTOM_KEYCODE_END_HANDLER,
  WORD_LAYER_0_HANDLER,
  WORD_LAYER_1_HANDLER,
  WORD_LAYER_2_HANDLER,
  WORD_LAYER_3_HANDLER,
  WORD_LAYER_4_HANDLER,
  WORD_LAYER_5_HANDLER,
  WORD_LAYER_6_HANDLER,
  WORD_LAYER_7_HANDLER,
  MOUSE_SPEED_UP_HANDLER,
  MOUSE_SPEED_DOWN_HANDLER,
  SCROLL_SPEED_UP_HANDLER,
  SCROLL_SPEED_DOWN_HANDLER,
};

bool IncrementMouseSpeed(keyrecord_t *record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    joystick_mouse_speed_increment(1);
  }
  return false;
}
bool DecrementMouseSpeed(keyrecord_t *record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    joystick_mouse_speed_decrement(1);
  }
  return false;
}
bool IncrementScrollSpeed(keyrecord_t *record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    joystick_scroll_speed_increment(1);
  }
  return false;
}
bool DecrementScrollSpeed(keyrecord_t *record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    joystick_scroll_speed_decrement(1);
  }
  return false;
}

custom_keycode_handler_t custom_keycode_handlers[] = {
  [ALT_TAB_HANDLER] = CK_HANDLER_FN(AltTabHandler),
  [SHIFT_ALT_TAB_HANDLER] = CK_HANDLER_FN(AltShiftTabHandler),
  [LR_ALT_B_BUTTON_HANDLER] = CK_HANDLER_FN(AltBButtonHandler),
  [OUTLOOK_RELOAD_HANDLER] = CK_HANDLER_FN(OutlookTodayHandler),
  [WORD_LAYER_0_HANDLER] = WORD_HANDLER_FUNC(0),
  [WORD_LAYER_1_HANDLER] = WORD_HANDLER_FUNC(1),
  [WORD_LAYER_2_HANDLER] = WORD_HANDLER_FUNC(2),
  [WORD_LAYER_3_HANDLER] = WORD_HANDLER_FUNC(3),
  [WORD_LAYER_4_HANDLER] = WORD_HANDLER_FUNC(4),
  [WORD_LAYER_5_HANDLER] = WORD_HANDLER_FUNC(5),
  [WORD_LAYER_6_HANDLER] = WORD_HANDLER_FUNC(6),
  [WORD_LAYER_7_HANDLER] = WORD_HANDLER_FUNC(7),
  [MOUSE_SPEED_UP_HANDLER] = CK_HANDLER_FN(IncrementMouseSpeed),
  [MOUSE_SPEED_DOWN_HANDLER] = CK_HANDLER_FN(DecrementMouseSpeed),
  [SCROLL_SPEED_UP_HANDLER] = CK_HANDLER_FN(IncrementScrollSpeed),
  [SCROLL_SPEED_DOWN_HANDLER] = CK_HANDLER_FN(DecrementScrollSpeed),
};

#define CK_ALTB CK(LR_ALT_B_BUTTON_HANDLER)
#define CK_ATAB CK(ALT_TAB_HANDLER)
#define CK_STAB CK(SHIFT_ALT_TAB_HANDLER)
#define CK_OLRL CK(OUTLOOK_RELOAD_HANDLER)
#define CK_WL_0 CK(WORD_LAYER_0_HANDLER)
#define CK_WL_1 CK(WORD_LAYER_1_HANDLER)
#define CK_WL_2 CK(WORD_LAYER_2_HANDLER)
#define CK_WL_3 CK(WORD_LAYER_3_HANDLER)
#define CK_WL_4 CK(WORD_LAYER_4_HANDLER)
#define CK_WL_5 CK(WORD_LAYER_5_HANDLER)
#define CK_WL_6 CK(WORD_LAYER_6_HANDLER)
#define CK_WL_7 CK(WORD_LAYER_7_HANDLER)
#define CK_MSUP CK(MOUSE_SPEED_UP_HANDLER)
#define CK_MSDN CK(MOUSE_SPEED_DOWN_HANDLER)
#define CK_SCUP CK(SCROLL_SPEED_UP_HANDLER)
#define CK_SCDN CK(SCROLL_SPEED_DOWN_HANDLER)

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

/* TODO:
- ctrl-click
- ctrl-shift-click
- GU(TAB)
- ctrl+f
- links
  - chime
  - id grabber (press url_copy key n times for n-th id?)
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LAYOUT_xbox(
                _______,                                              _______,
                TK_LB,                                                TK_RB,
                                           _______,                   SH(TAB),
                TK_COPY,          TK_SLCT,          TK_STRT, KC_TAB,           KC_BTN2,
                CK_ATAB,                   KC_PRINT_SCREEN,           KC_BTN1,
       TK_LEFT,          TK_RGHT,                   TK_PSTE,
                CK_STAB
    ),

    [LR_ALT] = LAYOUT_xbox(
                _______,                                              _______,
                _______,                                              _______,
                                           _______,                   _______,
                _______,          _______,          _______, _______,          CK_ALTB,
                CK_ATAB,                   _______,                   _______,
       _______,          _______,                   _______,
                CK_STAB
    ),

    [LR_OUTLOOK] = LAYOUT_xbox(
                _______,                                              _______,
                _______,                                              _______,
                                           _______,                   OL_PREV,
                _______,          _______,          CK_OLRL, OL_DEL,           _______,
                _______,                   _______,                   OL_NEXT,
       _______,          _______,                   _______,
                _______
                // TODO: Dpad for calendar functions (left, right, today)
    ),

    [LR_TYPE] = LAYOUT_xbox(
                MO(LR_SYMB),                                          KC_RSFT,
                _______,                                              CK_WL_4,
                                           _______,                   CK_WL_3,
                KC_0,             KC_ESC,           _______, CK_WL_2,             CK_WL_1,
                CK_WL_6,                   _______,                   CK_WL_0,
       CK_WL_5,          KC_RIGHT,                  _______,
                CK_WL_7
    ),

    [LR_SYMB] = LAYOUT_xbox(
                _______,                                              KC_RSFT,
                _______,                                              CK_WL_4,
                                           _______,                   CK_WL_3,
                KC_0,             KC_ESC,           _______, CK_WL_2,             CK_WL_1,
                KC_UP,                     _______,                   KC_X,
       KC_LEFT,          KC_RIGHT,                  _______,
                KC_DOWN
    ),

    [LR_SETTINGS] = LAYOUT_xbox(
                _______,                                              _______,
                _______,                                              _______,
                                           _______,                   _______,
                _______,          _______,         _______, _______,             _______,
                CK_MSUP,                   _______,                   _______,
       CK_SCDN,          CK_SCUP,                  _______,
                CK_MSDN
    ),
};
