// TODO: Move this to v2 and let each keyboard implement
// actual instances individually.

// NOTE: This doesn't work with some keycodes such as tap dance keys that exist in the
// second layer (e.g. TO_SCRL/SCRR in LR_ONE_HAND_LEFT/RIGHT)

/* Issue: when typing fast, would want to type " d". However, the space
key is also the symbol layer, so the following would happen:

- Press symbol key (for space presumably)
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

// These two weights are multiplied by the amount of time spent in the overlap
// layer vs not while the overlap key is pressed.
// This gives extra weight to either choice when determining whether we should
// consider the overlap press as being done in the symbol layer or not,
//
// For example, if these weights are 2 (layer) and 3 (not layer) respectively,
// then the threshold for making the decision is when the key is pressed for
// 3/5 the time in the symbol layer and 2/5 the time in the not layer
// > Note that this implies that we are *more* likely to side with the not layer.
#define SYMBOL_LAYER_OVERLAP_LAYER_COEFFICIENT 2
#define SYMBOL_LAYER_OVERLAP_OTHER_COEFFICIENT 3

layer_overlap_handler_t symbol_handler = {
    .first_symb_press_key_pos  = {},
    .first_symb_press_keycode  = KC_NO,
    .first_symb_press          = false,
    .resolved_first_symb_press = true,
    .layer                     = LR_SYMB,
    .keycode                   = TO_SYMB_KEYCODE,
    .osm_keycode               = TO_SYMB,

    .key_press_at          = 0,
    .key_in_layer_duration = 0,
};

layer_overlap_handler_t ctrl_overlap_handler = {
    .first_symb_press_key_pos  = {},
    .first_symb_press_keycode  = KC_NO,
    .first_symb_press          = false,
    .resolved_first_symb_press = true,
    .layer                     = LR_CTRL,
    .keycode                   = KC_ENTER,
    .osm_keycode               = TO_CTRL,

    .key_press_at          = 0,
    .key_in_layer_duration = 0,
};

// No longer need handlers for oh left/right layers because we use a combo to
// activate those layers now

// Logic for stuff

void SymbolLayerOverlap_reset(bool activated, layer_overlap_handler_t *handler) {
  if (activated) {
    handler->first_symb_press          = false;
    handler->resolved_first_symb_press = true;
  } else {
    handler->key_in_layer_duration = timer_elapsed32(handler->key_press_at);
  }
}

bool SymbolLayerOverlap_handled(layer_overlap_handler_t *handler, uint16_t keycode, keyrecord_t *record) {
    // Need to ensure we don't check the osm key itself.
    if (keycode == handler->osm_keycode) {

        // Record the key position of the osm keycode
        if (record->event.pressed) {
            handler->osm_keycode_key_pos  = ((keypos_t){
                    .col = record->event.key.col,
                    .row = record->event.key.row,
            });
            return false;
        }

        // If we already resolved it then proceed as normal
        if (!handler->first_symb_press) {
            return false;
        }
        layer_off(handler->layer);

        // It's worth noting that if this returns true, then the tap dance will not have been reset!
        // We could send a key event to trigger the interrupt and then return false, (TODO: try this instead?: just call process_tap_dance or whatever to fake an interrupt)
        // but instead we take care of it below.
        return !handler->resolved_first_symb_press;
    }

    bool in_symb_layer = IS_LAYER_ON(handler->layer);

    if (!handler->resolved_first_symb_press) {
        handler->resolved_first_symb_press = true;

        // This block handles the following scenario:
        // * Press and hold symbol layer key
        // * Press and hold second key
        // * Press third key (that is neither symbol layer key nor second key)
        // In this scenario, we assume that:
        // 1. The symbol layer key is being pressed and held
        // 2. The second key is being press and held in the symbol layer
        // 3. The third key is being processed on top of that
        // TODO: Can this logic be done in pre_process_record_user?!
        if (keycode != handler->first_symb_press_keycode) {

            // First press the second key
            // uint16_t second_keycode = handler->first_symb_press_keycode;
            keyevent_t second_event = {
                .key = handler->first_symb_press_key_pos,
                .type = KEY_EVENT,
                .pressed = true,
                .time = timer_read(),
            };
            action_exec(second_event);

            // Simulate the press of the third key (but possibly in a different layer)
            keyevent_t third_event = {
                .key = record->event.key,
                .type = KEY_EVENT,
                .pressed = true,
                .time = timer_read(),
            };
            action_exec(third_event);

            // Skip handling of third key (since we simulated press above)
            return true;
        }

        // key_in_layer_duration: duration of time the key was down while in the symbol layer
        // key_out_layer_duration: duration of time the key was down while NOT in the symbol layer
        // Consider the following key events:
        // (osm key press) ------ (other key press) ------- (osm key release) -------- (other key release)
        //                                | key_in_layer_duration |
        //                                                        |   key_out_layer_duration   |
        uint32_t key_out_layer_duration = timer_elapsed32(handler->key_press_at) - handler->key_in_layer_duration;

        // Determine if the key was held down longer in the overlap layer or not
        bool in_overlap_layer_longer = (SYMBOL_LAYER_OVERLAP_LAYER_COEFFICIENT * handler->key_in_layer_duration) > (SYMBOL_LAYER_OVERLAP_OTHER_COEFFICIENT * key_out_layer_duration);

        // If we're not in the symbol layer, then the following happened:
        // - Press symb key
        // - Press other key
        // - Unpress symb key
        // - Unpress other key
        // and we meant to just "type" the symb key as a space key.
        if (!in_symb_layer && !in_overlap_layer_longer) {
            tap_code16(handler->keycode);
        }

        // Tap the key we didn't press yet (don't use tap_code16 because it can
        // be a tap dance, custom keycode, etc. and we rather just let action_exec
        // handle it).

        // Temporarily change the layer back if in_overlap_layer_longer
        if (in_overlap_layer_longer) {
            layer_on(handler->layer);
        }

        // Simulate the press and release of the key
        keyevent_t second_event = {
            .key = handler->first_symb_press_key_pos,
            .type = KEY_EVENT,
            .pressed = true,
            .time = timer_read(),
        };
        action_exec(second_event);
        keyevent_t second_event_release = {
            .key = handler->first_symb_press_key_pos,
            .type = KEY_EVENT,
            .pressed = false,
            .time = timer_read(),
        };
        action_exec(second_event_release);

        if (in_overlap_layer_longer) {
            layer_off(handler->layer);
        }

        // Simulate the release of the key that got us to the OSM layer
        // to ensure the tap dance is reset (since it wasn't due to skip in `keycode == handler->osm_keycode` check).
        keyevent_t regular_key_release = {
            .key = handler->osm_keycode_key_pos,
            .type = KEY_EVENT,
            .pressed = false,
            .time = timer_read(),
        };
        action_exec(regular_key_release);

        /***************
         * Old logic below.
         * Benefit of old logic: didn't do layer_on/layer_off which can have side effects
         * Disbenefit of old logic: Had to re-implement relevant action_exec depending on things which wasn't great
         * Cons definitely outweighs the pros, so we keep the new logic above
         ***************/

        // uint16_t actual_keycode = keymap_key_to_keycode(in_overlap_layer_longer ? handler->layer : get_highest_layer(layer_state), handler->first_symb_press_key_pos);
        // if (actual_keycode >= QK_TAP_DANCE && actual_keycode <= QK_TAP_DANCE_MAX) {
        //     // If key in other layer is a tap dance (but in this layer is just a regular key),
        //     // then we need to execute the press and unpress logic for it.
        //     bool original_press   = record->event.pressed;
        //     record->event.pressed = true;
        //     preprocess_tap_dance(actual_keycode, record);
        //     process_tap_dance(actual_keycode, record);
        //     record->event.pressed = false;
        //     preprocess_tap_dance(actual_keycode, record);
        //     process_tap_dance(actual_keycode, record);
        //     record->event.pressed = original_press;
        // } else if (IS_CUSTOM_KEYCODE(actual_keycode)) {
        //     bool original_press   = record->event.pressed;
        //     record->event.pressed = true;
        //     process_custom_keycodes(actual_keycode, record);
        //     record->event.pressed = false;
        //     process_custom_keycodes(actual_keycode, record);
        //     record->event.pressed = original_press;
        // } else {
        //     // Otherwise, just press the regular keycode
        //     tap_code16(actual_keycode);
        // }

        // Deactivate alt mode if we did a quick alt mode key
        // and are now out of the layer.
        if (!in_symb_layer) {
            end_alt_tab_mode();
        }

        return (handler->first_symb_press_key_pos.col == record->event.key.col && handler->first_symb_press_key_pos.row == record->event.key.row);
    }

    // Record the first key press in the symbol layer, but don't actually press it.
    if (in_symb_layer && !handler->first_symb_press && record->event.pressed) {
        handler->key_press_at = timer_read32();
        handler->first_symb_press          = true;
        handler->first_symb_press_keycode  = keycode;
        handler->first_symb_press_key_pos  = ((keypos_t){
                 .col = record->event.key.col,
                 .row = record->event.key.row,
        });

        bool needs_layer_overlap_logic = (record->event.type != COMBO_EVENT);

        // If it needs layer-overlap logic, then it has *not* been resolved
        handler->resolved_first_symb_press = !needs_layer_overlap_logic;

        // If it doesn't need layer-overlap logic, then we shouldn't mark this as handled
        return needs_layer_overlap_logic;
    }
    return false;
}
