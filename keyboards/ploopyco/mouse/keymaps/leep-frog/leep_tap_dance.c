#pragma once

/********************** COPIED FROM qmk_firmware package **********************/

// See below link for following functions
// https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_tap_dance.md#setup
enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5, // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7
};

#define SS_COPY SS_RCTL(SS_TAP(X_INSERT))
#define SS_PASTE SS_RSFT(SS_TAP(X_INSERT))

int cur_dance(tap_dance_state_t *state, bool interrupt_matters) {
    if (state->count == 1) {
        if ((interrupt_matters && state->interrupted) || !state->pressed) {
            return SINGLE_TAP;
            // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.

        // NOTE: These lines have also been changed (check state->pressed before checking state->interrupted)
        if (state->pressed) {
            return DOUBLE_HOLD;
        } else if (state->interrupted) {
            return DOUBLE_SINGLE_TAP;
        } else {
            return DOUBLE_TAP;
        }
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TRIPLE_TAP;
        } else {
            return TRIPLE_HOLD;
        }
    } else {
        return 8; // magic number. At some point this method will expand to work for more presses
    }
}

/********************** END COPY **********************/

/****************** CLICK_HOLD START ******************/

typedef union {
    uint16_t hold_int;
    char hold_string[13];
} leep_hold_value_t;

#define HOLD_INT(i) { .hold_int = i }
#define HOLD_STRING(s) { .hold_string = s "\0" }

typedef void (*leep_hold_fn_t)(tap_dance_state_t *state, bool finished, leep_hold_value_t *hold_value);

typedef struct {
    uint16_t kc;
    leep_hold_value_t hold_value;
    leep_hold_fn_t hold_fn;
} leep_td_user_data_t;

void leep_td_each_press(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    if (state->count > 1) {
        // First click (count == 1) is sent on unpress, so only send subsequent clicks.
        register_code16(ud->kc);
    }
}

void leep_td_each_unpress(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    if (state->count == 1) {
        /* If the dance isn't finished then click
        // (if the dance is finished, then we reached a HOLD or INTERRUPT state,
        // in which case the key was used as a layer change).*/
        if (!state->finished) {
            tap_code16(ud->kc);
        }
    } else {
        /* Otherwise, just regular un-click */
        unregister_code16(ud->kc);
    }
}

void leep_td_finished(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    // This accounts for holds or interrupts (and is run before interrupting key).
    if ((cur_dance(state, false) == SINGLE_HOLD)) {
        if (ud->hold_fn) {
            ud->hold_fn(state, true, &(ud->hold_value));
        }
    }
}

void leep_td_reset(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;
    if (ud->hold_fn) {
        ud->hold_fn(state, false, &(ud->hold_value));
    }
}

// Click to hold KC
void leep_kc_hold_fn(tap_dance_state_t *state, bool finished, leep_hold_value_t *hv) {
    if (finished) {
        tap_code16(hv->hold_int);
    }
}
#define LEEP_TD_CLICK_TO_HOLD_KC(kc, hold_kc) \
    { .fn = {leep_td_each_press, leep_td_each_unpress, leep_td_finished, leep_td_reset}, .user_data = (void *)&((leep_td_user_data_t){kc, HOLD_INT(hold_kc), leep_kc_hold_fn}), }

// Click to hold layer
void leep_layer_hold_fn(tap_dance_state_t *state, bool finished, leep_hold_value_t *hv) {
    if (finished) {
        layer_on(hv->hold_int);
    } else {
        layer_off(hv->hold_int);
    }
}
#define LEEP_TD_CLICK_TO_HOLD_LAYER(kc, layer) \
    { .fn = {leep_td_each_press, leep_td_each_unpress, leep_td_finished, leep_td_reset}, .user_data = (void *)&((leep_td_user_data_t){kc, HOLD_INT(layer), leep_layer_hold_fn}), }

// Click to hold custom fn
#define LEEP_TD_CLICK_TO_HOLD_FN(kc, hold_fn, hold_value) \
    { .fn = {leep_td_each_press, leep_td_each_unpress, leep_td_finished, leep_td_reset}, .user_data = (void *)&((leep_td_user_data_t){kc, hold_value, hold_fn}), }

/******************* CLICK_HOLD END *******************/

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

void tdk_ctrl_tab_fn(tap_dance_state_t *state, bool finished, leep_hold_value_t *hv) {
    if (finished) {
        del_weak_mods(state->weak_mods);
        send_string(hv->hold_string);
    } else {
        SEND_STRING(SS_DOWN(X_RCTL));
    }
}

/*void tdk_ctrl_shift_tab_fn(tap_dance_state_t *state, bool finished, uint16_t value) {
    if (finished) {
        del_weak_mods(state->weak_mods);
        // clear_mods();
        SEND_STRING(SS_UP(X_RCTL) SS_RALT(SS_TAP(value)));
    } else {
        SEND_STRING(SS_DOWN(X_RCTL));
    }
}*/

tap_dance_action_t tap_dance_actions[] = {
    // Alt dance
    [TDK_ALT] = LEEP_TD_CLICK_TO_HOLD_LAYER(KC_BTN3, LR_ALT),
    // Ctrl dance
    [TDK_CTRL] = LEEP_TD_CLICK_TO_HOLD_LAYER(KC_BTN1, LR_CTRL),
    // Ctrl+tab or next page in browser
    [TDK_CTRL_TAB] = LEEP_TD_CLICK_TO_HOLD_FN(KC_TAB, &tdk_ctrl_tab_fn, HOLD_STRING(SS_UP(X_RCTL) SS_RALT(SS_TAP(X_RIGHT)))),
    // Ctrl+shift+tab of previous page in browser
    [TDK_CTRL_STAB] = LEEP_TD_CLICK_TO_HOLD_FN(S(KC_TAB), &tdk_ctrl_tab_fn, HOLD_STRING(SS_UP(X_RCTL) SS_RALT(SS_TAP(X_LEFT)))),
    // WS dance
    [TDK_WORKSPACE] = LEEP_TD_CLICK_TO_HOLD_LAYER(KC_BTN2, LR_WS),
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
    [TDK_OUTLOOK_READ] = LEEP_TD_CLICK_TO_HOLD_KC(OL_MARK_READ, OL_MARK_UNREAD),
    // VSCode definition dance
    [TDK_VSCODE_DEFINITION] = ACTION_TAP_DANCE_FN(td_vscode_definition),
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
#define TD_VDEF TD(TDK_VSCODE_DEFINITION)
