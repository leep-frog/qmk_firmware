#pragma once

#include "../v2/leep_tap_dance_v2.h"
// #include "record.c"
// #include "shift.c"

// The shift and symbol tap dances change layers which requires special logic.
// If we just use the logic above (SINGLE_TAP, DOUBLE_TAP, etc. cases), then we
// have the following issue:
// - Do tap dance (DOUBLE_TAP_HOLD let's say) to change layer
// - press another key before tapping_term is up
// - the key is pressed in the original layer, not in the layer we are
//   trying to change to.

// SHIFT TAP DANCE
/*int shift_press_count = 0;

void shift_each_press(tap_dance_state_t *state, void *user_data) {
    switch (++shift_press_count) {
        case 1:
            SEND_STRING(SS_DOWN(X_RSFT));
            LEEP_SOLID_COLOR(BLUE, false);
            break;
        case 2:
            layer_on(LR_ONE_HAND_LEFT);
            SymbolLayerOverlap_reset(&lr_left_handler);
            break;
        case 3:
            SEND_STRING(SS_TAP(X_ENTER) SS_TAP(X_ENTER));
            // Notice no 'break' here, so we just press a third enter
            // by falling to the default case.
        default:
            // Undo previous press and then press again.
            SEND_STRING(SS_DOWN(X_ENTER));
            break;
    }
}

void shift_each_unpress(tap_dance_state_t *state, void *user_data) {
    switch (shift_press_count) {
        case 1:
            SEND_STRING(SS_UP(X_RSFT));
            LEEP_LAYER_COLOR(LR_BASE, false);
            break;
        case 2:
            layer_off(LR_ONE_HAND_LEFT);
            break;
        default:
            SEND_STRING(SS_UP(X_ENTER));
            break;
    }
}

void shift_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, false)) {
        case SINGLE_TAP:
            SEND_STRING(SS_TAP(X_ENTER));
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            SEND_STRING(SS_TAP(X_ENTER) SS_TAP(X_ENTER));
            break;
    }
}

void shift_reset(tap_dance_state_t *state, void *user_data) {
    shift_press_count = 0;
}

// SYMB TAP DANCE
int symb_press_count = 0;

void symb_each_press(tap_dance_state_t *state, void *user_data) {
    switch (++symb_press_count) {
        case 1:
            layer_on(LR_SYMB);
            SymbolLayerOverlap_reset(&symbol_handler);
            break;
        case 2:
            layer_on(LR_ONE_HAND_RIGHT);
            SymbolLayerOverlap_reset(&lr_right_handler);
            break;
        case 3:
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_SPACE));
            // Notice no 'break' here, so we just press a third space
            // by falling to the default case.
        default:
            SEND_STRING(SS_DOWN(X_SPACE));
            break;
    }
}

void symb_each_unpress(tap_dance_state_t *state, void *user_data) {
    switch (symb_press_count) {
        case 1:
            layer_off(LR_SYMB);
            break;
        case 2:
            layer_off(LR_ONE_HAND_RIGHT);
            break;
        default:
            SEND_STRING(SS_UP(X_SPACE));
            break;
    }
}

void symb_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, false)) {
        case SINGLE_TAP:
            SEND_STRING(SS_TAP(X_SPACE));
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_SPACE));
            break;
    }
}

void symb_reset(tap_dance_state_t *state, void *user_data) {
    symb_press_count = 0;
}*/

// Ctrl-t tap dance
void td_ctrl_t(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            SEND_STRING(SS_RCTL("t"));
            break;
        case DOUBLE_TAP:
            SEND_STRING(SS_RCTL(SS_RSFT(SS_TAP(X_T))));
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                SEND_STRING(SS_RCTL("t"));
            }
            break;
    }
}

// char *universal_backspace = SS_RCTL(SS_TAP(X_BSPACE) SS_RALT(SS_TAP(X_H)));
// Removed ctrl+alt+h. That was used for bash backspace, but realized
// that we can use 'bind' or 'bindkey' in bash environments to bind
// ctrl+backspace to "backward-kill-word" (found with `bind -P | grep word`)
// char *universal_backspace = SS_RCTL(SS_TAP(X_BSPACE));

void TDMarkdownPaste(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("]");
        return;
    }

    // Finish markdown link
    if (state->count == 2) {
        SEND_STRING("](" SS_PASTE ")");
        return;
    }

    SEND_STRING(">>" SS_PASTE "]]");
}

void TDOutlookReload(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Switch panes
        send_string(SS_RCTL(SS_RSFT(SS_TAP(X_TAB))));
        // Reload
        tap_code16(KC_F5);
        // Swtich panes again
        send_string(SS_RCTL(SS_TAP(X_TAB)));
        return;
    }
    // Otherwise, only reload
    tap_code16(KC_F5);
}

void tda(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            // Select all
            SEND_STRING(SS_RCTL("a"));
            break;
        case DOUBLE_HOLD:
            // Select all and copy
            SEND_STRING(SS_RCTL("ac"));
            SNG_COPY();
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(KC_A);
            }
            break;
    }
}

void un_tda(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_A);
}

void tdb(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            SEND_STRING(SS_RCTL("b"));
            break;
        case DOUBLE_HOLD:
            // Bulleted list
            SEND_STRING(SS_RCTL(SS_RSFT("8")));
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(KC_B);
            }
            break;
    }
}

void un_tdb(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_B);
}

void tdc(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            // Copy
            SEND_STRING(SS_RCTL("c"));
            SNG_COPY();
            break;
        case DOUBLE_HOLD:
            URL_COPY();
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(KC_C);
            }
            break;
    }
}

void un_tdc(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_C);
}

void tdi(tap_dance_state_t *state, void *user_data) {
  if (!state->pressed || state->interrupted) {
    // Dance finished as a tap
    for (int i = 0; i < state->count; i++) {
        tap_code16(KC_I);
    }
    return;
  }

  if (state->count == 1) {
    CR_ID();
    return;
  }

  // Dance ended with a hold
  SEND_STRING(FOCUS_TAB_STRING() SS_TAP(X_RIGHT) SS_DOWN(X_RCTL));
  for (int i = 2; i < state->count; i++) {
    SEND_STRING(SS_TAP(X_LEFT));
  }
  if (state->count != 2) {
    SEND_STRING(SS_UP(X_RCTL) SS_TAP(X_LEFT) SS_DOWN(X_RCTL));
  }
  SEND_STRING(SS_RSFT(SS_TAP(X_LEFT)) "c" SS_UP(X_RCTL));
}

void tds(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            tap_code16(KC_PRINT_SCREEN);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(KC_S);
            }
            break;
    }
}

void un_tds(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_S);
}

void tdu(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            URL_COPY();
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(KC_U);
            }
            break;
    }
}

void un_tdu(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_U);
}

void paste_or_type(tap_dance_state_t *state, void *user_data, uint16_t keycode) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            SEND_STRING(SS_PASTE);
            break;
        case DOUBLE_HOLD:
            URL_PASTE();
            break;
        case TRIPLE_TAP:
            // Paste without formatting
            SEND_STRING(SS_RCTL(SS_RSFT("v")));
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                register_code16(keycode);
            }
            break;
    }
}

void tdv(tap_dance_state_t *state, void *user_data) {
    paste_or_type(state, user_data, KC_V);
}

void un_tdv(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_V);
}

void tdy(tap_dance_state_t *state, void *user_data) {
    paste_or_type(state, user_data, KC_Y);
}

void un_tdy(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_Y);
}

void oh_copy(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_COPY);
        return;
    }

    URL_COPY();
}

void oh_paste(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_PASTE);
        return;
    }

    URL_PASTE();
}

void scroll_press_left(tap_dance_state_t *state, void *user_data) {
    layer_on(LR_SCROLL);
    if (state->count == 1) {
        return;
    }
    if (state->count == 2) {
        SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_LEFT))));
    }
    SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_LEFT))));
}

void scroll_press_right(tap_dance_state_t *state, void *user_data) {
    layer_on(LR_SCROLL);
    if (state->count == 1) {
        return;
    }
    if (state->count == 2) {
        SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_RIGHT))));
    }
    SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_RIGHT))));
}

void scroll_unpress(tap_dance_state_t *state, void *user_data) {
    layer_off(LR_SCROLL);
}

void scroll_left_finished(tap_dance_state_t *state, void *user_data) {
    if (cur_dance(state, true) == SINGLE_TAP && !state->interrupted) {
        SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_LEFT))));
    }
}

void scroll_right_finished(tap_dance_state_t *state, void *user_data) {
    if (cur_dance(state, true) == SINGLE_TAP && !state->interrupted) {
        SEND_STRING(SS_RCTL(SS_RGUI(SS_TAP(X_RIGHT))));
    }
}

void ella_mode(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case TRIPLE_TAP:
            layer_off(LR_ELLA);
            break;
    }
}

bool pinky_shifted = false;

void pinky_start_fn(tap_dance_state_t *state, bool press, leep_td_value_t *hold_value) {
  if (press) {
    pinky_shifted = get_mods() & MOD_MASK_SHIFT;
  }
}

void pinky_press_fn(tap_dance_state_t *state, bool tap, leep_td_value_t *hold_value) {
  bool currently_shifted = get_mods() & MOD_MASK_SHIFT;
  bool shift_override = false;
  if (tap && pinky_shifted && !currently_shifted) {
    add_mods(MOD_BIT(KC_RSFT));
    shift_override = true;
  }

  leep_kc_press_fn(state, tap, hold_value);
  if (shift_override) {
    del_mods(MOD_BIT(KC_RSFT));
  }
}

tap_dance_action_t tap_dance_actions[] = {
    // Shift toggle
    // [TDK_SHIFT_TOGGLE] = ACTION_TAP_DANCE_FN(TDToggleShift),
    [TDK_SHIFT_TOGGLE] = LEEP_TD_CLICK_KC_HOLD_FN(C(KC_J), TDToggleShift_hold, LEEP_TD_NOVAL()),
    // Kill line
    [TDK_KILL_LINE] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, TDKillLine_finished, TDKillLine_reset),
    // Record 1
    [TDK_MACRO_1] = ACTION_TAP_DANCE_FN(Record1Function),
    // Record 2
    [TDK_MACRO_2] = ACTION_TAP_DANCE_FN(Record2Function),
    // Markdown paste
    [TDK_MARKDOWN_PASTE] = ACTION_TAP_DANCE_FN(TDMarkdownPaste),
    // Outlook reload
    [TDK_OUTLOOK_RELOAD] = ACTION_TAP_DANCE_FN(TDOutlookReload),
    // 'A' tap dance
    [TDK_A] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tda, un_tda),
    // 'B' tap dance
    [TDK_B] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdb, un_tdb),
    // 'C' tap dance
    [TDK_C] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdc, un_tdc),
    // 'I' tap dance
    [TDK_I] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdi, NULL),
    // 'S' tap dance
    [TDK_S] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tds, un_tds),
    // 'U' tap dance
    [TDK_U] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdu, un_tdu),
    // 'V' tap dance
    [TDK_V] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdv, un_tdv),
    // 'Y' tap dance
    [TDK_Y] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, NULL, tdy, un_tdy),
    // Ctrl-t tap dance
    [TDK_CTL_T] = ACTION_TAP_DANCE_FN(td_ctrl_t),
    // One hand copy
    [TDK_OH_COPY] = ACTION_TAP_DANCE_FN(oh_copy),
    // One hand paste
    [TDK_OH_PASTE] = ACTION_TAP_DANCE_FN(oh_paste),
    // Symbol layer
    [TDK_SYMB_LAYER] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_SPACE, LR_SYMB),
    // Shift layer
    [TDK_SHIFT_LAYER] = LEEP_TD_CLICK_KC_HOLD_HOLD_KC(KC_ENTER, KC_RSFT),
    // Scroll left layer
    [TDK_SCROLL_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(scroll_press_left, scroll_unpress, scroll_left_finished, NULL),
    // Scroll right layer
    [TDK_SCROLL_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(scroll_press_right, scroll_unpress, scroll_right_finished, NULL),
    // Outlook or semi-colon
    // [TDK_TO_OUTLOOK] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_SCLN, LR_OUTLOOK),
    [TDK_TO_OUTLOOK] = LEEP_TD_CLICK_HOLD(LEEP_TD_NOVAL(), pinky_start_fn, LEEP_TD_INT(KC_SCLN), pinky_press_fn, LEEP_TD_INT(LR_OUTLOOK), leep_layer_hold_fn),
    // Nav or windows key
    [TDK_TO_NAV] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_LGUI, LR_NAVIGATION),
    // Nav or windows key
    [TDK_TO_NAV_RCBR] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_RCBR, LR_NAVIGATION),
    // Shortcut or no key (for now)
    [TDK_TO_SHORTCUT] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_LCBR, LR_SHORTCUTS),
    // Shortcut or no key (for now)
    [TDK_ELLA_MODE] = ACTION_TAP_DANCE_FN(ella_mode),
};

#define TGL_SHF TD(TDK_SHIFT_TOGGLE)

bool IsToggleShiftTapDance(uint16_t keycode) {
  return (keycode == TGL_SHF);
}

#define CK_KILL TD(TDK_KILL_LINE)
#define CK_MCR1 TD(TDK_MACRO_1)
#define CK_MCR2 TD(TDK_MACRO_2)
#define CK_DEL_WORD RCTL(KC_DELETE)
#define CK_MDPS TD(TDK_MARKDOWN_PASTE)
// See here for outlook keyboard shortcuts:
// https://support.microsoft.com/en-us/office/keyboard-shortcuts-for-outlook-3cdeb221-7ae5-4c1d-8c1d-9e63216c1efd#PickTab=Windows
// Outlook reload
#define OL_RLD TD(TDK_OUTLOOK_RELOAD)
// Outlook move left pane
#define OL_LEFT RCTL(SH(TAB))
// Outlook move right pane
#define OL_RGHT KC_F6
#define TD_A TD(TDK_A)
#define TD_B TD(TDK_B)
#define TD_C TD(TDK_C)
#define TD_I TD(TDK_I)
#define TD_S TD(TDK_S)
#define TD_U TD(TDK_U)
#define TD_V TD(TDK_V)
#define TD_Y TD(TDK_Y)
#define TD_CTLT TD(TDK_CTL_T)
#define OH_COPY TD(TDK_OH_COPY)
#define OH_PSTE TD(TDK_OH_PASTE)
#define TO_SCRL TD(TDK_SCROLL_LEFT)
#define TO_SCRR TD(TDK_SCROLL_RIGHT)

#define TO_SFT TD(TDK_SHIFT_LAYER)
#define TO_SYMB TD(TDK_SYMB_LAYER)

#define TO_OTLK TD(TDK_TO_OUTLOOK)
#define TO_SHCT TD(TDK_TO_SHORTCUT)
#define TO_NAV TD(TDK_TO_NAV)
#define TO_NAVB TD(TDK_TO_NAV_RCBR)

#define TO_BASE_FROM_ELLA TD(TDK_ELLA_MODE)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Some functions I hold for a bit longer, which causes annoying behavior mid-typing
        case TD_A:
            return TAPPING_TERM + 50;
        case CK_MCR1:
        case CK_MCR2:
            // If not recording give extra time to double tap to start recording.
            if (!IsRecording()) {
                return TAPPING_TERM + 200;
            }
    }
    return TAPPING_TERM;
}
