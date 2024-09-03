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
  LR_BROWSER,
  LR_SHIFT,
};

enum custom_keycode_handlers {
  ALT_TAB_HANDLER,
  SHIFT_ALT_TAB_HANDLER,
};

custom_keycode_handler_t custom_keycode_handlers[] = {
  [ALT_TAB_HANDLER] = CK_HANDLER_FN(AltTabHandler),
  [SHIFT_ALT_TAB_HANDLER] = CK_HANDLER_FN(AltShiftTabHandler),
};

#define CK_ATAB CK(ALT_TAB_HANDLER)
#define CK_STAB CK(SHIFT_ALT_TAB_HANDLER)

uint16_t Alt_keycodes[] = {
  CK_ATAB,
  CK_STAB,
};

/**********
* Combos *
**********/

const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_C),
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
};

tap_dance_action_t tap_dance_actions[] = {
  [TDK_TO_SHIFT] = LEEP_TD_CLICK_KC_HOLD_LAYER(CK_STAB, LR_SHIFT),
  [TDK_TO_BROWSER] = LEEP_TD_CLICK_KC_HOLD_LAYER(WS_LEFT, LR_BROWSER),
  [TDK_BROWSER_1] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_CLOSE, CK_WWWB),
  [TDK_BROWSER_2] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_REOPEN, RCTL(KC_R)),
  [TDK_BROWSER_3] = LEEP_TD_CLICK_KC_HOLD_KC(CK_WWW_NEW, CK_WWWF),
};

#define CK_SHFT TD(TDK_TO_SHIFT)

#define CK_BRWS TD(TDK_TO_BROWSER)
#define CK_CLOSE_BACK TD(TDK_BROWSER_1)
#define CK_REOPEN_RELOAD TD(TDK_BROWSER_2)
#define CK_NEW_FORWARD TD(TDK_BROWSER_3)

/*************
* Main logic *
**************/

#define LR_ELLA LR_BASE // Needed for below include

#include "users/leep-frog/v2/leep_index_v2.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_BASE] = LAYOUT_pedals(
        CK_SHFT, CK_BRWS, CK_TABB, CK_TABF, WS_RGHT, KC_ENTER
    ),

    [LR_BROWSER] = LAYOUT_pedals(
        _______, _______, _______, CK_CLOSE_BACK, CK_REOPEN_RELOAD, CK_NEW_FORWARD
    ),

    [LR_SHIFT] = LAYOUT_pedals(
        _______, _______, _______, CK_MTBB, _______, CK_MTBF
    ),
};


// TODO: maybe space and/or tab?
// TODO: Have pedal-holds activate modifiers for use by keyboard (shift, ctrl, etc.)
// TODO: Shortcuts like print screen?
// TODO: Scroll layer?
// TODO: copy and paste
// TODO: outlook?
