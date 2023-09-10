
uint16_t blink_timer;
bool     blink_on = false;
bool recording    = false;

bool IsRecording(void) {
  return recording;
}

// Press twice, record
// Press once, stop if recording, otherwise play
// TODO: Settings object
bool processing_macro = false;

void recorder_base(tap_dance_state_t *state, uint16_t play_action, uint16_t start_action) {
    // This check ensures we never get into an infinite macro loop.
    if (processing_macro) {
        return;
    }

    // See below link for details on implementation:
    // https://www.reddit.com/r/olkb/comments/co39nc/help_cant_get_dynamic_macros_working_with_tap/
    keyrecord_t kr;
    kr.event.pressed = false;
    uint16_t action  = play_action;
    bool     macro_1 = play_action == QK_DYNAMIC_MACRO_PLAY_1;

    bool valid = false;
    // Note: we *only* press enter on initial recording save, and NOT on
    // macro playback (to avoid accidentally putting passwords anywhere like
    // in chats).
    bool press_enter = false;

    switch (cur_dance(state, true)) {
        case SINGLE_TAP:
            if (recording) {
                valid            = true;
                action           = QK_DYNAMIC_MACRO_RECORD_STOP;
                kr.event.pressed = true;
                recording        = false;
                if (macro_1) {
                    SNG_REC_1_END();
                    press_enter = true;
                } else {
                    SNG_REC_2_END();
                }
                LEEP_SOLID_COLOR(GREEN, true);

            }
            break;
        case DOUBLE_TAP:
            if (!recording) {
                valid     = true;
                action    = start_action;
                recording = true;
                SNG_REC_START();
                LEEP_COLOR_MODE(RED, RGB_MATRIX_RAINBOW_MOVING_CHEVRON, true);
            }
            break;
        case DOUBLE_HOLD:
            if (!recording) {
                valid = true;
                if (macro_1) {
                    SNG_REC_1_PLAY();
                } else {
                    SNG_REC_2_PLAY();
                }
            }
    }

    if (!valid) {
        SNG_DUD();
    } else {
        processing_macro = true;
        process_dynamic_macro(action, &kr);
        processing_macro = false;
    }

    if (press_enter) {
        tap_code16(KC_ENTER);
    }
}

void Record1Function(tap_dance_state_t *state, void *user_data) { recorder_base(state, QK_DYNAMIC_MACRO_PLAY_1, QK_DYNAMIC_MACRO_RECORD_START_1); }

void Record2Function(tap_dance_state_t *state, void *user_data) { recorder_base(state, QK_DYNAMIC_MACRO_PLAY_2, QK_DYNAMIC_MACRO_RECORD_START_2); }
