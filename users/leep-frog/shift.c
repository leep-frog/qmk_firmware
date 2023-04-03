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

// Runs emacs shift toggle (ctrl-j) if hit once, otherwise activates shift
// toggle layer.
void TDToggleShift(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_RCTL("j"));
    } else {
        ToggleShift();
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
