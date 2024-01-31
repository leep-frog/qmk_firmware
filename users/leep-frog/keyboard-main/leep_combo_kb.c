
#include "leep_enum_kb.h"

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
  return PlayedStartupSong();
}


static void end_tap_dance(bool pressed) {
    keyevent_t leep_event = (keyevent_t){
        // Pressed is used by preprocess_tap_dance and we need it to be true, otherwise nothing happens.
        // If statement earlier ensures this.
        .pressed = pressed,
        // Key isn't used by preprocess_tap_dacne, so it can be anything. This value was just copy and pasted from tmk_core/common/keyboard.h
        .key = (keypos_t){.row = 255, .col = 255},
        // Time isn't used by preprocess_tap_dacne, so it can be anything.
        .time = 0,
    };
    keyrecord_t leep_record = {.event = leep_event};
    preprocess_tap_dance(0, &leep_record);
}

void internal_process_combo_event(uint16_t combo_index, bool pressed);
void process_combo_event(uint16_t combo_index, bool pressed) {
  internal_process_combo_event(combo_index, pressed);
  OSM_combo_cleanup();
}

void internal_process_combo_event(uint16_t combo_index, bool pressed) {
    // TODO: Add OSM_handle/cleanup since combos don't reach main function
    if (!pressed) {
      switch (combo_index) {
        case FENTER_OH_LEFT:
          layer_off(LR_ONE_HAND_LEFT);
          break;
        case JSPACE_OH_RIGHT:
          layer_off(LR_ONE_HAND_RIGHT);
          break;
      }
      return;
    }

    // Tap dances aren't interrupted properly in this function because this
    // function is run during preprocess_* (and does not advance to process_*).
    // Meanwhile, tap dance termination is done in the process_* logic. To
    // ensure any open tap dances are properly terminated, we explicitly end
    // them here.
    // Specific error that this fixes:
    // - Press tap dance key (e.g. "i")
    // - Before tap dance termination, activate combo that runs COMBO_ACTION (e.g. "DF_QUOTE")
    //   (note this isn't an issue for other combos that just run COMBO(...))
    // - Combo action will execute before tap dance does resulting in ("i) even
    //   though we expect to get (i").
    end_tap_dance(pressed);

    switch (combo_index) {
        case DF_QUOTE:
            // See below link for more info on get_mods and mod masks.
            // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
            if (get_mods() & MOD_MASK_SHIFT) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT) "'" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT) "'" SS_DOWN(X_RSFT));
                }
            } else {
                SEND_STRING("\"");
            }
            break;
        case FENTER_OH_LEFT:
          layer_on(LR_ONE_HAND_LEFT);
          break;
        case JSPACE_OH_RIGHT:
          layer_on(LR_ONE_HAND_RIGHT);
          break;
    }
}
