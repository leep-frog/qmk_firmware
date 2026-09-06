
#include "./leep_layers_v2.h"
#include "./leep_color_v2.h"

bool shift_toggled       = false;

bool IsShiftToggled(void) {
  return shift_toggled;
}

void ToggleShift(void) {
    if (shift_toggled) {
        // Turn off shift.
        SEND_STRING(SS_UP(X_RSFT));
        LEEP_LAYER_COLOR(LeepHighestLayer, true);
    } else {
        // Turn on shift.
        LEEP_COLOR_MODE(RED, RGB_MATRIX_RAINBOW_PINWHEELS, true);
        SEND_STRING(SS_DOWN(X_RSFT));
    }
    shift_toggled = !shift_toggled;
}

bool UnsetShift(void) {
    if (shift_toggled) {
        ToggleShift();
    }
    return true;
}

void TDToggleShift_hold(tap_dance_state_t *state, bool finished, leep_td_value_t *hv) {
    // Only run on finished (not on reset).
    if (!finished) {
        return;
    }

    // If we were interrupted, then we probably were actually just trying to tap the key.
    if (state->interrupted && state->count == 1) {
        tap_code16(C(KC_J));
        return;
    }

    // Otherwise, it's a legit hold.
    ToggleShift();
    if (shift_toggled) {
        SNG_COPY();
    } else {
        SNG_PASTE();
    }
}

bool kill_line_hold = false;

// Runs emacs line kill (ctrl-k) if hit once, otherwise emulates behavior for regular text things.
void TDKillLine_finished(tap_dance_state_t *state, void *user_data) {
    // While in shift mode, both a tap and a hold should just run the full kill-and-yank sequence.
    if (shift_toggled) {
        UnsetShift();
        // The tap dance framework snapshots the mods active at the initial
        // tap (here, RSFT from shift mode) as "weak mods" that get replayed
        // on top of whatever we send until this dance's reset runs. Without
        // clearing that now, the RSFT above would leak into ctrl+k (sending
        // ctrl+shift+k) and into the final enter (sending shift+enter).
        clear_weak_mods();
        SEND_STRING(SS_RCTL("k") SS_DELAY(100) SS_PASTE SS_DELAY(50) SS_TAP(X_ENTER));
        return;
    }

    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
            // Only press ctrl+k here. Releasing will result in the paste/enter. That way, flow is:
            // * Start holding ctrl+k (ctrl+k is pressed)
            // * Wait for dialog to pop up (ctrl+k is still pressed)
            // * Release ctrl+k (ctrl+k is released, and paste+enter is sent)
            kill_line_hold = true;
            SEND_STRING(SS_RCTL("k"));
            break;
        case DOUBLE_TAP:
            // Copy the rest of the line.
            if (!shift_toggled) {
                ToggleShift();
            }
            SEND_STRING(SS_TAP(X_END));
            ToggleShift();

            // Copy and delete it.
            SEND_STRING(SS_RCTL("c") SS_TAP(X_DELETE));
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                SEND_STRING(SS_RCTL("k"));
            }
            break;
    }
}

// See SINGLE_HOLD case above as for why this is necessary.
void TDKillLine_reset(tap_dance_state_t *state, void *user_data) {
    // Using cur_dance doesn't work here (maybe the code thinks there's an interrupt when not?),
    // hence why we maintain and use our own kill_line_hold variable here instead.
    if (kill_line_hold) {
        kill_line_hold = false;
        SEND_STRING(SS_PASTE SS_DELAY(50) SS_TAP(X_ENTER));
    }
}

bool _ctrl_g_new(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        if (shift_toggled) {
            ToggleShift();
        } else {
            SEND_STRING(SS_RCTL("g"));
        }
    }
    return true;
}
