static bool pending_ctrl_x = false;

#define LEEP_CTRL_X_DELAY_MS 30

bool to_ctrl_x_layer(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        pending_ctrl_x = true;
        ActivateOneshot(LR_CTRL_X);
    }
    return false;
}

void ctrl_x_layer_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!(pending_ctrl_x && record->event.pressed)) {
        return;
    }

    pending_ctrl_x = false;
    bool should_send_ctrl_x = true;
    switch (keycode) {
        case CK_TGSH:
        case CK_PASTE: // CL(Y):
            should_send_ctrl_x = false;
            break;
    }

    if (should_send_ctrl_x) {
        SEND_STRING(SS_RCTL("x"));
        wait_ms(LEEP_CTRL_X_DELAY_MS);
    }
}
