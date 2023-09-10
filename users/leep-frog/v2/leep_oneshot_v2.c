// Made this file because built-in one-shot logic wasn't
// working properly. Specifically, the ctrl+x layer wouldn't
// be activated while in oneshot mode, so the code in the ctrl layer
// would be sent regardless if implemented via my layer hook logic
// or as a custom keycode.

static uint16_t leep_oneshot_layer = 0;
static bool leep_oneshot_key_pressed = false;

// Note: this does not support nested one shots.
void ActivateOneshot(uint16_t layer) {
    if (!leep_oneshot_key_pressed) {
        leep_oneshot_layer = layer;
        layer_on(layer);
        leep_oneshot_key_pressed = true;
    }
}

void Oneshot_handled(keyrecord_t* record) {
    // Do nothing if a key pressed
    if (record->event.pressed) {
        return;
    }

    // Unpress the one shot key
    if (leep_oneshot_key_pressed) {
        leep_oneshot_key_pressed = false;
        return;
    }

    // Deactivate the oneshot layer after the second key press
    if (leep_oneshot_layer) {
        layer_off(leep_oneshot_layer);
        leep_oneshot_layer = 0;
    }
}
