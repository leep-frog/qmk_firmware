#ifndef LEEP_SHIFT
#define LEEP_SHIFT

void ToggleShift(void) {
    if (shift_toggled) {
        // Turn off shift.
        SEND_STRING(SS_UP(X_RSFT));
        LEEP_LAYER_COLOR(LR_CTRL, true);
    } else {
        // Turn on shift.
        LEEP_COLOR_MODE(RED, RGB_MATRIX_RAINBOW_PINWHEELS, true);
        SEND_STRING(SS_DOWN(X_RSFT));
    }
    shift_toggled = !shift_toggled;
}

bool UntoggleShift(void) {
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
    switch (cur_dance(state, true)) {
        case SINGLE_HOLD:
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

void TDKillLine_reset(tap_dance_state_t *state, void *user_data) {
    // Using cur_dance doesn't work here (maybe the code thinks there's an interrupt when not?),
    // hence why we maintain and use our own kill_line_hold variable here instead.
    if (kill_line_hold) {
        kill_line_hold = false;
        SEND_STRING(SS_PASTE);
    }
}

void _ctrl_g_new(bool pressed) {
    if (pressed) {
        if (shift_toggled) {
            ToggleShift();
        } else {
            SEND_STRING(SS_RCTL("g"));
        }
    }
}

#endif
