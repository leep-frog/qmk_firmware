#ifndef LEEP_FEATURE_SYMBOL_LAYER_OVERLAP
#define LEEP_FEATURE_SYMBOL_LAYER_OVERLAP

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

// Logic for stuff
static keypos_t first_symb_press_key      = {};
static bool     first_symb_press          = false;
static bool     resolved_first_symb_press = true;

void SymbolLayerOverlap_reset(void) {
    first_symb_press          = false;
    resolved_first_symb_press = true;
}

bool SymbolLayerOverlap_handled(uint16_t keycode, keyrecord_t *record) {
    // Need to ensure we don't check the symbol key itself.
    // We can do a more accurate check, but the following is simple enough
    // and works for all keys for which the main issue is occurring.
    if (keycode > QK_MODS_MAX) {
        return false;
    }

    bool symb_layer = IS_LAYER_ON(LR_SYMB);

    if (!resolved_first_symb_press) {
        resolved_first_symb_press = true;
        // If we're not in the symbol layer, then the following happened:
        // - Press symb key
        // - Press other key
        // - Unpress symb key
        // - Unpress other key
        // and we meant to just "type" the symb key as a space key.
        if (!symb_layer) {
            SEND_STRING(" ");
        }

        // Send the key we didn't press yet.
        uint16_t actual_keycode = keymap_key_to_keycode(get_highest_layer(layer_state), first_symb_press_key);
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

        return (first_symb_press_key.col == record->event.key.col && first_symb_press_key.row == record->event.key.row);
    }

    // Record the first key press in the symbol layer, but don't actually press it.
    if (symb_layer && !first_symb_press && record->event.pressed) {
        first_symb_press          = true;
        first_symb_press_key      = ((keypos_t){
                 .col = record->event.key.col,
                 .row = record->event.key.row,
        });
        resolved_first_symb_press = false;
        return true;
    }
    return false;
}

#endif
