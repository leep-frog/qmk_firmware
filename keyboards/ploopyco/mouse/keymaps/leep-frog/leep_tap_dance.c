#pragma once

// Needed for leep_url_v2.h import
// (which is indirectly imported by leep_tap_dance_v2)
void SNG_COPY(void) {}

#include "../../../../../users/leep-frog/v2/leep_tap_dance_v2.c"
#include "../../../../../users/leep-frog/v2/leep_codes_v2.h"

// TDK_COPY_PASTE

void td_copy_paste(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, false)) {
        case SINGLE_TAP:
            SEND_STRING(SS_COPY);
            break;
        case SINGLE_HOLD:
            SEND_STRING(SS_PASTE);
            break;
        case DOUBLE_TAP:
            URL_COPY();
            break;
        case DOUBLE_HOLD:
            URL_PASTE();
            break;
    }
}

// TDK_CLOSE_TAB

bool move_tab = false;

void td_hold_close_tab(tap_dance_state_t *state, bool tap, leep_td_value_t *hv) {
  move_tab = state->pressed;
}

// TDK_CTRL_[S]TAB

void td_ctrl_tab(tap_dance_state_t *state, bool tap, leep_td_value_t *hv) {
  leep_td_value_t v = LEEP_TD_INT(move_tab ? C(S(KC_PGDN)) : C(KC_TAB));
  leep_kc_press_fn(state, tap, &v);
}

void td_ctrl_shift_tab(tap_dance_state_t *state, bool tap, leep_td_value_t *hv) {
  leep_td_value_t v = LEEP_TD_INT(move_tab ? C(S(KC_PGUP)) : C(S(KC_TAB)));
  leep_kc_press_fn(state, tap, &v);
}

// TDK_BOOT

// LEEP_TD_CLICK_TO_HOLD_KC_* doesn't work with custom keycodes (QK_BOOT), hence why
// we need to create this function.
void td_boot(tap_dance_state_t *state, void *user_data) {
    reset_keyboard();
}

// TDK_WORKSPACE

// modeled after leep_kc_press_fn
void td_workspace_press_fn(tap_dance_state_t *state, bool tap, leep_td_value_t *hv) {
    // Key is on first tap.
    if (tap) {
        SEND_STRING(SS_DOWN(X_RCTL) SS_DOWN(X_RSFT) SS_DELAY(25) SS_TAP(X_BTN1) SS_DELAY(25) SS_UP(X_RCTL) SS_UP(X_RSFT));
        return;
    }

    // Can't really add additional logic here because the tap code will still be run first.
}

void _leep_code_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    if (finished) {
        hv->td_bool ? SEND_STRING(LEEP_CODE_1) : SEND_STRING(LEEP_CODE_2);
    }
}


tap_dance_action_t tap_dance_actions[] = {
    // Alt dance
    [TDK_ALT] = LEEP_TD_CLICK_KC_HOLD_LAYER_ON_FIRST_CLICK_ONLY(KC_BTN3, LR_ALT),
    // Ctrl dance
    [TDK_CTRL] = LEEP_TD_CLICK_KC_HOLD_LAYER(C(KC_T), LR_CTRL),
    // Ctrl+tab or next page in browser
    [TDK_CTRL_TAB] = LEEP_TD_CLICK_FN_HOLD_KC(td_ctrl_tab, LEEP_TD_NOVAL(), A(KC_RIGHT)),
    // Ctrl+shift+tab of previous page in browser
    [TDK_CTRL_STAB] = LEEP_TD_CLICK_FN_HOLD_KC(td_ctrl_shift_tab, LEEP_TD_NOVAL(), A(KC_LEFT)),
    // WS dance
    [TDK_WORKSPACE] = LEEP_TD_CLICK_FN_HOLD_LAYER(td_workspace_press_fn, LEEP_TD_NOVAL(), LR_WS),
    // Copy, paste dance
    [TDK_COPY_PASTE] = ACTION_TAP_DANCE_FN(td_copy_paste),
    // Reload/re-open tab dance
    [TDK_REOPEN_RELOAD_TAB] = LEEP_TD_CLICK_KC_HOLD_KC(C(KC_R), C(S(KC_T))),
    // Win+tab, code 1
    [TDK_WIN_TAB] = LEEP_TD_CLICK_KC_HOLD_FN(G(KC_TAB), _leep_code_fn, LEEP_TD_BOOL(true)),
    // Print screen, code 2
    [TDK_PRINT_SCREEN] = LEEP_TD_CLICK_KC_HOLD_FN(KC_PRINT_SCREEN, _leep_code_fn, LEEP_TD_BOOL(false)),
    // Reboot
    [TDK_BOOT] = ACTION_TAP_DANCE_FN(td_boot),
};

#define TO_ALT TD(TDK_ALT)
#define TO_CTRL TD(TDK_CTRL)
#define TO_WS TD(TDK_WORKSPACE)

#define TD_CFWD TD(TDK_CTRL_TAB)
#define TD_CBCK TD(TDK_CTRL_STAB)
#define TD_COPY_PASTE TD(TDK_COPY_PASTE)
#define TD_OTAB TD(TDK_OPEN_TAB)
#define TD_CTAB TD(TDK_CLOSE_TAB)
#define OL_RLD TD(TDK_OUTLOOK_RELOAD)
#define OL_RDTD TD(TDK_OUTLOOK_READ)
#define OL_DEL TD(TDK_OUTLOOK_DELETE)
#define TD_VDEF TD(TDK_VSCODE_DEFINITION)
#define TD_BOOT TD(TDK_BOOT)

#define TD_REOPEN_RELOAD_TAB TD(TDK_REOPEN_RELOAD_TAB)
#define TD_WIN_TAB TD(TDK_WIN_TAB)
#define TD_PRINT_SCREEN TD(TDK_PRINT_SCREEN)
