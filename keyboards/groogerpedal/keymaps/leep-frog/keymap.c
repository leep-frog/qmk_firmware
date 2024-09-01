// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "quantum/leep/custom_keycode_handler.h"

#include "../../../../users/leep-frog/v2/leep_aliases_v2.h"
#include "../../../../users/leep-frog/v2/leep_alt_v2.h"
#include "../../../../users/leep-frog/v2/leep_custom_keycodes_v2.h"
#include "../../../../users/leep-frog/v2/leep_workspace_v2.h"

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_pedals(
        CK_STAB, WS_LEFT, CK_TABB, CK_ATAB, WS_RGHT, CK_TABF
    )
};

enum leep_tap_dances {
  TDK_ABC = 0,
};

tap_dance_action_t tap_dance_actions[] = {
  // [TDK_ABC] = LEEP_TD_CLICK_KC_HOLD_LAYER(WS_RIGHT, LR_OUTLOOK),
};
