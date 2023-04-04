#pragma once

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

typedef union {
    uint16_t td_int;
    // TODO: Make this a pointer to save space
    char td_string[13];
} leep_td_value_t;

#define LEEP_TD_INT(i) { .td_int = i }
#define LEEP_TD_STRING(s) { .td_string = s "\0" }
#define LEEP_TD_NOVAL() LEEP_TD_INT(0)

typedef void (*leep_hold_fn_t)(tap_dance_state_t *state, bool finished, leep_td_value_t *hold_value);

// Press function will be called once for the first tap (click+unclick) and then separately for each subsequent click and unclick.
// The `tap` argument will be set to `true` if the function is being executed for the first tap. Otherwise,
// the function should check the `state` argument for the `count` and `pressed` fields to determine which press/unpress
// the dance is at.
typedef void (*leep_press_fn_t)(tap_dance_state_t *state, bool tap, leep_td_value_t *hold_value);

typedef struct {
    leep_td_value_t press_value;
    leep_press_fn_t press_fn;
    leep_td_value_t hold_value;
    leep_hold_fn_t hold_fn;
} leep_td_user_data_t;

void leep_td_noop_fn(tap_dance_state_t *state, bool arg, leep_td_value_t *user_data) { }

void leep_td_each_press(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    if (state->count > 1) {
        // First click (count == 1) is sent on unpress, so only send subsequent clicks.
        // ~register_code16(ud->kc);
        if (ud->press_fn) {
            ud->press_fn(state, false, &(ud->press_value));
        }
    }
}

void leep_td_each_unpress(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    if (state->count == 1) {
        /* If the dance isn't finished then click
        // (if the dance is finished, then we reached a HOLD or INTERRUPT state,
        // in which case the key was used as a layer change).*/
        if (!state->finished) {
            // ~tap_code16(ud->kc);
            if (ud->press_fn) {
                ud->press_fn(state, true, &(ud->press_value));
            }
        }
    } else {
        /* Otherwise, just regular un-click */
        // ~unregister_code16(ud->kc);
        if (ud->press_fn) {
            ud->press_fn(state, false, &(ud->press_value));
        }
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

// Macro to create function for this
#define LEEP_TD_CLICK_HOLD(press_value, press_fn, hold_value, hold_fn) \
    { .fn = {leep_td_each_press, leep_td_each_unpress, leep_td_finished, leep_td_reset}, .user_data = (void *)&((leep_td_user_data_t){press_value, press_fn, hold_value, hold_fn}), }

// press KC fn
void leep_kc_press_fn(tap_dance_state_t *state, bool tap, leep_td_value_t *hv) {
    // Key is on first tap.
    if (tap) {
        tap_code16(hv->td_int);
        return;
    }

    // On subsequent clicks so either register or unregister accordingly.
    if (state->pressed) {
        register_code16(hv->td_int);
    } else {
        unregister_code16(hv->td_int);
    }
}

// hold KC fn
void leep_kc_hold_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    if (finished) {
        tap_code16(hv->td_int);
    }
}
#define LEEP_TD_CLICK_KC_HOLD_KC(kc, hold_kc) LEEP_TD_CLICK_HOLD(LEEP_TD_INT(kc), leep_kc_press_fn, LEEP_TD_INT(hold_kc), leep_kc_hold_fn)

// Click to hold layer
void leep_layer_hold_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    if (finished) {
        layer_on(hv->td_int);
    } else {
        layer_off(hv->td_int);
    }
}
#define LEEP_TD_CLICK_KC_HOLD_LAYER(kc, layer) LEEP_TD_CLICK_HOLD(LEEP_TD_INT(kc), leep_kc_press_fn, LEEP_TD_INT(layer), leep_layer_hold_fn)

#define LEEP_TD_CLICK_FN_HOLD_LAYER(press_fn, press_value, layer) LEEP_TD_CLICK_HOLD(press_value, press_fn, LEEP_TD_INT(layer), leep_layer_hold_fn)

#define LEEP_TD_CLICK_KC_HOLD_FN(kc, hold_fn, hold_value) LEEP_TD_CLICK_HOLD(LEEP_TD_INT(kc), leep_kc_press_fn, hold_value, hold_fn)

#define LEEP_TD_CLICK_FN_HOLD_FN(press_fn, press_value, hold_fn, hold_value) LEEP_TD_CLICK_HOLD(press_value, press_fn, hold_value, hold_fn)
