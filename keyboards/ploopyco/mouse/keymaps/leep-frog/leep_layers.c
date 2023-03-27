#pragma once

bool layers_status[NUM_LAYERS] = {
    [0]                    = true,
    [1 ... NUM_LAYERS - 1] = false,
};

void layer_change_alt(bool activated) {
    if (!activated) {
        deactivate_alt();
    }
}

void layer_change_ctrl(bool activated) {
    if (activated) {
        SEND_STRING(SS_DOWN(X_RCTL));
    } else {
        SEND_STRING(SS_UP(X_RCTL));
    }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    // Run processors
    for (int i = 0; i < NUM_LAYERS; i++) {
        bool current_state = layer_state_cmp(state, i);
        if (current_state != layers_status[i]) {
            layers_status[i] = current_state;
            switch (i) {
                case LR_ALT:
                    layer_change_alt(current_state);
                    break;
                case LR_CTRL:
                    layer_change_ctrl(current_state);
                    break;
            }

        }
    }

    return state;
}

// Initially tried to do this via the pointing_device_task_user function (https://docs.qmk.fm/#/feature_pointing_device?id=manipulating-mouse-reports),
// but the report_mouse_t returned by the function (for ploopyco at least) isn't used for scrolling.
// Instead, I added this method in `ploopyco/.../mouse.c` and implemented it here.
bool transpose_scrolling(void) {
    return IS_LAYER_ON(LR_WS);
}
