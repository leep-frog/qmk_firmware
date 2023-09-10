// TODO: Move this to v2 and let each keyboard implement
// actual instances individually.

// NOTE: This doesn't work with some keycodes such as tap dance keys that exist in the
// second layer (e.g. TO_SCRL/SCRR in LR_ONE_HAND_LEFT/RIGHT)

/* Issue: when typing fast, would want to type " d". However, the space
key is also the symbol layer, so the following would happen:

- Press symbol key (for space presumable)
- Press another key (e.g. d)
- Unpress symbol key
- Unpress another key

This results in sending "$" when we actually wanted to send " d".

This feature file implements a fix for this issue.

Test cases:
1. See above sequence
2. See above sequence, but with a tap dance key in the non-symbol layer (e.g. "a/&" key).
3. Press a key in the symbol layer
4. Symbol key press, press 1, press 2, press 3, unpress 1, unpress 2, unpress 3, unpress symbol key.
   This tests the issue where we resolve the first_symb_press due to another key being pressed (as
   opposed to unpressing the first_symb_press).
*/

layer_overlap_handler_t symbol_handler = {
    .first_symb_press_key      = {},
    .first_symb_press          = false,
    .resolved_first_symb_press = true,
    .layer                     = LR_SYMB,
    .keycode                   = " ",
};

layer_overlap_handler_t lr_left_handler = {
    .first_symb_press_key      = {},
    .first_symb_press          = false,
    .resolved_first_symb_press = true,
    .layer                     = LR_ONE_HAND_LEFT,
    .keycode                   = "\n\n",
};

layer_overlap_handler_t lr_right_handler = {
    .first_symb_press_key      = {},
    .first_symb_press          = false,
    .resolved_first_symb_press = true,
    .layer                     = LR_ONE_HAND_RIGHT,
    .keycode                   = "  ",
};

// Logic for stuff

void SymbolLayerOverlap_reset(layer_overlap_handler_t *handler) {
    handler->first_symb_press          = false;
    handler->resolved_first_symb_press = true;
}

bool SymbolLayerOverlap_handled(layer_overlap_handler_t *handler, uint16_t keycode, keyrecord_t *record) {
    // Need to ensure we don't check the symbol key itself.
    // We can do a more accurate check, but the following is simple enough
    // and works for all keys for which the main issue is occurring.
    if (keycode > QK_MODS_MAX) {
        return false;
    }

    bool symb_layer = IS_LAYER_ON(handler->layer);

    if (!handler->resolved_first_symb_press) {
        handler->resolved_first_symb_press = true;
        // If we're not in the symbol layer, then the following happened:
        // - Press symb key
        // - Press other key
        // - Unpress symb key
        // - Unpress other key
        // and we meant to just "type" the symb key as a space key.
        if (!symb_layer) {
            send_string(handler->keycode);
        }

        // Send the key we didn't press yet.
        uint16_t actual_keycode = keymap_key_to_keycode(get_highest_layer(layer_state), handler->first_symb_press_key);
        if (actual_keycode >= QK_TAP_DANCE && actual_keycode <= QK_TAP_DANCE_MAX) {
            // If key in other layer is a tap dance (but in this layer is just a regular key),
            // then we need to execute the press and unpress logic for it.
            bool original_press   = record->event.pressed;
            record->event.pressed = true;
            preprocess_tap_dance(actual_keycode, record);
            process_tap_dance(actual_keycode, record);
            record->event.pressed = false;
            preprocess_tap_dance(actual_keycode, record);
            process_tap_dance(actual_keycode, record);
            record->event.pressed = original_press;
        } else {
            // Otherwise, just press the regular keycode
            tap_code16(actual_keycode);
        }

        return (handler->first_symb_press_key.col == record->event.key.col && handler->first_symb_press_key.row == record->event.key.row);
    }

    // Record the first key press in the symbol layer, but don't actually press it.
    if (symb_layer && !handler->first_symb_press && record->event.pressed) {
        handler->first_symb_press          = true;
        handler->first_symb_press_key      = ((keypos_t){
                 .col = record->event.key.col,
                 .row = record->event.key.row,
        });
        handler->resolved_first_symb_press = false;
        return true;
    }
    return false;
}
