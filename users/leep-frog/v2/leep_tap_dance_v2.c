#pragma once

#include "leep_tap_dance_v2.h"
#include "leep_url_v2.h"
#include "leep_aliases_v2.h"

int cur_dance(tap_dance_state_t *state, bool interrupt_while_holding_means_tap) {
    if (state->count == 1) {
        if (!state->pressed || (interrupt_while_holding_means_tap && state->interrupted)) {
            return SINGLE_TAP;
            // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.

        if (!state->pressed) {
          return DOUBLE_TAP;
        } else if (interrupt_while_holding_means_tap && state->interrupted) {
          return DOUBLE_SINGLE_TAP;
        } else {
          return DOUBLE_HOLD;
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

void leep_td_noop_fn(tap_dance_state_t *state, bool arg, leep_td_value_t *user_data) { }

void leep_td_each_press(tap_dance_state_t *state, void *user_data) {
    leep_td_user_data_t *ud = (leep_td_user_data_t *)user_data;

    if (state->count == 1) {
      if (ud->dance_start_fn) {
        ud->dance_start_fn(state, &(ud->press_value));
      }
    } else {
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

// Click to hold layer
void leep_layer_hold_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    if (finished) {
        layer_on(hv->td_int);
    } else {
        layer_off(hv->td_int);
    }
}

/***************************************
 * Below are common tap dance handlers *
 ***************************************/

void LeepTD_url_copy_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
  if (finished) {
    URL_COPY();
  }
}

void LeepTD_url_paste_fn(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
  if (finished) {
    URL_PASTE();
  }
}
