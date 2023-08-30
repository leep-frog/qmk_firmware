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

int cur_dance(tap_dance_state_t *state, bool interrupt_matters);

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

typedef void (*leep_dance_start_fn_t)(tap_dance_state_t *state, leep_td_value_t *hold_value);

typedef struct {
    leep_dance_start_fn_t dance_start_fn;
    leep_td_value_t press_value;
    leep_press_fn_t press_fn;
    leep_td_value_t hold_value;
    leep_hold_fn_t hold_fn;
} leep_td_user_data_t;

void leep_td_noop_fn(tap_dance_state_t *state, bool arg, leep_td_value_t *user_data);
void leep_td_each_press(tap_dance_state_t *state, void *user_data);
void leep_td_each_unpress(tap_dance_state_t *state, void *user_data);
void leep_td_finished(tap_dance_state_t *state, void *user_data);
void leep_td_reset(tap_dance_state_t *state, void *user_data);
void leep_kc_press_fn(tap_dance_state_t *state, bool tap, leep_td_value_t *hv);
void leep_kc_hold_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);
void leep_layer_hold_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);

#define LEEP_TD_CLICK_HOLD(start_fn, press_value, press_fn, hold_value, hold_fn) \
    { .fn = {leep_td_each_press, leep_td_finished, leep_td_reset, leep_td_each_unpress}, .user_data = (void *)&((leep_td_user_data_t){start_fn, press_value, press_fn, hold_value, hold_fn}), }

#define LEEP_TD_CLICK_KC_HOLD_KC(kc, hold_kc) LEEP_TD_CLICK_HOLD(NULL, LEEP_TD_INT(kc), leep_kc_press_fn, LEEP_TD_INT(hold_kc), leep_kc_hold_fn)

#define LEEP_TD_CLICK_KC_HOLD_LAYER(kc, layer) LEEP_TD_CLICK_HOLD(NULL, LEEP_TD_INT(kc), leep_kc_press_fn, LEEP_TD_INT(layer), leep_layer_hold_fn)

#define LEEP_TD_CLICK_FN_HOLD_LAYER(press_fn, press_value, layer) LEEP_TD_CLICK_HOLD(NULL, press_value, press_fn, LEEP_TD_INT(layer), leep_layer_hold_fn)

#define LEEP_TD_CLICK_KC_HOLD_FN(kc, hold_fn, hold_value) LEEP_TD_CLICK_HOLD(NULL, LEEP_TD_INT(kc), leep_kc_press_fn, hold_value, hold_fn)

#define LEEP_TD_CLICK_FN_HOLD_FN(press_fn, press_value, hold_fn, hold_value) LEEP_TD_CLICK_HOLD(NULL, press_value, press_fn, hold_value, hold_fn)

// Below are common tap dance handlers

void LeepTD_url_copy_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);
void LeepTD_url_paste_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);
