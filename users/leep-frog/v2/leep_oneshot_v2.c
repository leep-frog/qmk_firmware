// Made this file because built-in one-shot logic wasn't
// working properly. Specifically, the ctrl+x layer wouldn't
// be activated while in oneshot mode, so the code in the ctrl layer
// would be sent regardless if implemented via my layer hook logic
// or as a custom keycode.

static uint16_t leep_oneshot_layer = 0;
static bool leep_oneshot_awaiting_action = false;
static keypos_t leep_oneshot_action_keypos;

// Note: this does not support nested one shots.
void ActivateOneshot(uint16_t layer) {
    if (!leep_oneshot_layer) {
        leep_oneshot_layer = layer;
        layer_on(layer);
        leep_oneshot_awaiting_action = true;
    }
}

void Oneshot_handled(keyrecord_t* record) {
    if (!leep_oneshot_layer) {
        return;
    }

    if (record->event.pressed) {
        // The first key pressed while the oneshot layer is active is the
        // "action" key (e.g. the J in ctrl+x j). Remember its position so
        // that only *its* release ends the oneshot below. Previously this
        // just counted releases (1st = the activating key, 2nd = the
        // action key), which broke if some other held key (e.g. the
        // layer's hold key) happened to release in between, prematurely
        // deactivating the layer before the action key was even pressed.
        if (leep_oneshot_awaiting_action) {
            leep_oneshot_awaiting_action = false;
            leep_oneshot_action_keypos = record->event.key;
        }
        return;
    }

    // Ignore releases of any key other than the action key (including the
    // key that activated the oneshot, and any key released before the
    // action key was even pressed).
    if (leep_oneshot_awaiting_action || !KEYEQ(record->event.key, leep_oneshot_action_keypos)) {
        return;
    }

    layer_off(leep_oneshot_layer);
    leep_oneshot_layer = 0;
}
