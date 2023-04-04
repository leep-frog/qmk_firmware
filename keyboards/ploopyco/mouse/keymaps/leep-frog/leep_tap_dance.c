#pragma once

#include "../../../../../users/leep-frog/v2/leep_tap_dance_v2.c"

// TDK_COPY

void td_copy_pressed(tap_dance_state_t *state, void *user_data) {
    layer_on(LR_KB);
}

void td_copy_unpressed(tap_dance_state_t *state, void *user_data) {
    layer_off(LR_KB);
}

void td_copy_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, false)) {
        case SINGLE_TAP:
            SEND_STRING(SS_COPY);
            break;
        // case SINGLE_HOLD: layer_on(LR_KB) is done by [un]pressed functions
        case DOUBLE_TAP:
            URL_COPY();
            break;
    }
}

// TDK_PASTE

void td_paste_pressed(tap_dance_state_t *state, void *user_data) {
    layer_on(LR_POWER_KB);
}

void td_paste_unpressed(tap_dance_state_t *state, void *user_data) {
    layer_off(LR_POWER_KB);
}

void td_paste_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, false)) {
        case SINGLE_TAP:
            SEND_STRING(SS_PASTE);
            break;
        // case SINGLE_HOLD: layer_on(LR_KB) is done by [un]pressed functions
        case DOUBLE_TAP:
            URL_PASTE();
            break;
    }
}

// TDK_OPEN_TAB

void td_open_tab(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            // Re-open closed tab (ctrl is held down by LR_CTRL layer logic)
            SEND_STRING(SS_RSFT("t"));
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                SEND_STRING("t");
            }
            break;
    }
}

// TDK_CLOSE_TAB

void td_close_tab(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            // Reload tab (ctrl is held down by LR_CTRL layer logic)
            SEND_STRING("r");
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                SEND_STRING("w");
            }
            break;
    }
}

// TDK_OUTLOOK_RELOAD

void td_outlook_reload(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            // Switch panes
            send_string(SS_RCTL(SS_RSFT(SS_TAP(X_TAB))));
            // Reload
            tap_code16(KC_F5);
            // Swtich panes again
            send_string(SS_RCTL(SS_TAP(X_TAB)));
            break;
        case SINGLE_HOLD:
            // Today in calendar view.
            SEND_STRING(SS_RALT(SS_TAP(X_H)) SS_TAP(X_O) SS_TAP(X_D));
            break;
        default:
            tap_code16(KC_F5);
    }
}

// TDK_VSCODE_DEFINITION

void td_vscode_definition(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            // Go to definition (ctrl+x ctrl+d)
            SEND_STRING(SS_RCTL("xd"));
            break;
        case SINGLE_HOLD:
            // Go to definition in separate window (ctrl+shift+d)
            SEND_STRING(SS_RCTL(SS_RSFT("d")));
            break;
    }
}

// TDK_CTRL_[SHIFT_]TAB

void tdk_ctrl_tab_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    if (finished) {
        del_weak_mods(state->weak_mods);
        send_string(hv->td_string);
    } else {
        SEND_STRING(SS_DOWN(X_RCTL));
    }
}

// TDK_BOOT

// LEEP_TD_CLICK_TO_HOLD_KC_* doesn't work with custom keycodes (QK_BOOT), hence why
// we need to create this function.
void td_boot(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            reset_keyboard();
            break;
        case SINGLE_HOLD:
            SEND_STRING(SS_RGUI("l"));
            break;
    }
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

tap_dance_action_t tap_dance_actions[] = {
    // Alt dance
    [TDK_ALT] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_BTN3, LR_ALT),
    // Ctrl dance
    [TDK_CTRL] = LEEP_TD_CLICK_KC_HOLD_LAYER(KC_BTN1, LR_CTRL),
    // Ctrl+tab or next page in browser
    [TDK_CTRL_TAB] = LEEP_TD_CLICK_KC_HOLD_FN(KC_TAB, tdk_ctrl_tab_fn, LEEP_TD_STRING(SS_UP(X_RCTL) SS_RALT(SS_TAP(X_RIGHT)))),
    // Ctrl+shift+tab of previous page in browser
    [TDK_CTRL_STAB] = LEEP_TD_CLICK_KC_HOLD_FN(S(KC_TAB), tdk_ctrl_tab_fn, LEEP_TD_STRING(SS_UP(X_RCTL) SS_RALT(SS_TAP(X_LEFT)))),
    // WS dance
    [TDK_WORKSPACE] = LEEP_TD_CLICK_FN_HOLD_LAYER(td_workspace_press_fn, LEEP_TD_NOVAL(), LR_WS),
    // Copy dance
    [TDK_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(td_copy_pressed, td_copy_unpressed, td_copy_finished, NULL),
    // Paste dance
    [TDK_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(td_paste_pressed, td_paste_unpressed, td_paste_finished, NULL),
    // Open tab dance
    [TDK_OPEN_TAB] = ACTION_TAP_DANCE_FN(td_open_tab),
    // Close tab dance
    [TDK_CLOSE_TAB] = ACTION_TAP_DANCE_FN(td_close_tab),
    // Outlook dance
    [TDK_OUTLOOK_RELOAD] = ACTION_TAP_DANCE_FN(td_outlook_reload),
    // Outlook dance
    [TDK_OUTLOOK_READ] = LEEP_TD_CLICK_KC_HOLD_KC(OL_MARK_READ, OL_MARK_UNREAD),
    // Outlook delete (use this so holding doesn't register key down and send multiple delete).
    [TDK_OUTLOOK_DELETE] = LEEP_TD_CLICK_KC_HOLD_KC(KC_DEL, KC_DEL),
    // VSCode definition dance
    [TDK_VSCODE_DEFINITION] = ACTION_TAP_DANCE_FN(td_vscode_definition),
    // Boot dance
    [TDK_BOOT] = ACTION_TAP_DANCE_FN(td_boot),
};

#define TO_ALT TD(TDK_ALT)
#define TO_CTRL TD(TDK_CTRL)
#define TO_WS TD(TDK_WORKSPACE)

#define TD_CFWD TD(TDK_CTRL_TAB)
#define TD_CBCK TD(TDK_CTRL_STAB)
#define TD_COPY TD(TDK_COPY)
#define TD_PASTE TD(TDK_PASTE)
#define TD_OTAB TD(TDK_OPEN_TAB)
#define TD_CTAB TD(TDK_CLOSE_TAB)
#define OL_RLD TD(TDK_OUTLOOK_RELOAD)
#define OL_RDTD TD(TDK_OUTLOOK_READ)
#define OL_DEL TD(TDK_OUTLOOK_DELETE)
#define TD_VDEF TD(TDK_VSCODE_DEFINITION)
// You can also put the mouse into boot mode by holding down the back thumb
// button down while plugging in the mouse.
#define TD_BOOT TD(TDK_BOOT)
