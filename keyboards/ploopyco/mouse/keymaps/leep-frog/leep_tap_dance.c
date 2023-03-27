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

typedef struct {
    uint16_t kc;
    uint16_t layer;
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

    if ((cur_dance(state, false) == SINGLE_HOLD)) {
        layer_on(ud->layer);
    }
}

void leep_td_reset(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;
    layer_off(ud->layer);
}

#define LEEP_TD_CLICK_HOLD(kc, layer) \
    { .fn = {leep_td_each_press, leep_td_each_unpress, leep_td_finished, leep_td_reset}, .user_data = (void *)&((leep_td_user_data_t){kc, layer}), }

/******************* CLICK_HOLD END *******************/

// TDK_COPY

void td_copy_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            SEND_STRING(SS_COPY);
            break;
        case SINGLE_HOLD:
            layer_on(LR_KB);
            break;
        case DOUBLE_TAP:
            URL_COPY();
            break;
    }
}

void td_copy_each_unpress(tap_dance_state_t *state, void *user_data) {
    layer_off(LR_KB);
}

// TDK_PASTE

void td_paste_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            SEND_STRING(SS_PASTE);
            break;
        case SINGLE_HOLD:
            register_code16(KC_BTN2);
            break;
        case DOUBLE_TAP:
            URL_PASTE();
    }
}

void td_paste_each_unpress(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_BTN2);
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

tap_dance_action_t tap_dance_actions[] = {
    // Alt dance
    [TDK_ALT] = LEEP_TD_CLICK_HOLD(KC_BTN2, LR_ALT),
    // Ctrl dance
    [TDK_CTRL] = LEEP_TD_CLICK_HOLD(KC_BTN1, LR_CTRL),
    // WS dance
    [TDK_WORKSPACE] = LEEP_TD_CLICK_HOLD(KC_BTN3, LR_WS),
    // Copy dance
    [TDK_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_copy_each_unpress, td_copy_finished, NULL),
    // Paste dance
    [TDK_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_paste_each_unpress, td_paste_finished, NULL),
    // Open tab dance
    [TDK_OPEN_TAB] = ACTION_TAP_DANCE_FN(td_open_tab),
    // Close tab dance
    [TDK_CLOSE_TAB] = ACTION_TAP_DANCE_FN(td_close_tab),
};

#define TO_ALT TD(TDK_ALT)
#define TO_CTRL TD(TDK_CTRL)
#define TO_WS TD(TDK_WORKSPACE)

#define TD_COPY TD(TDK_COPY)
#define TD_PASTE TD(TDK_PASTE)
#define TD_OTAB TD(TDK_OPEN_TAB)
#define TD_CTAB TD(TDK_CLOSE_TAB)
