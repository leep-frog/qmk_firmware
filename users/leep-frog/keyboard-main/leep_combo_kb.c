

// Combos
enum combos {
    JI_ESC,
    JK_HYPHEN,
    JL_EQUALS,
    KL_ENTER,
    DF_QUOTE,
    SD_TICK,
    FENTER_OH_LEFT,
    JSPACE_OH_RIGHT,
    // J_SEMICLN is still available,
    // SF is still an available combo slot.
    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM ji_combo[] = {KC_J, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_L, KC_J, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM fenter_combo[] = {KC_F, KC_ENTER, COMBO_END};
const uint16_t PROGMEM jspace_combo[] = {KC_J, KC_SPACE, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    // J+I = Escape
    [JI_ESC] = COMBO(ji_combo, KC_ESCAPE),
    // J+K = Hyphen
    [JK_HYPHEN] = COMBO(jk_combo, KC_MINUS),
    // J+L = Equals
    [JL_EQUALS] = COMBO(jl_combo, KC_EQUAL),
    // K+L = Enter
    [KL_ENTER] = COMBO(kl_combo, KC_ENTER),
    // D+F = Quote
    [DF_QUOTE] = COMBO_ACTION(df_combo),
    // S+D = Tick (`)
    [SD_TICK] = COMBO(sd_combo, KC_GRAVE),
    // F+Enter = LH layer
    [FENTER_OH_LEFT] = COMBO_ACTION(fenter_combo),
    // J+Space = RH layer
    [JSPACE_OH_RIGHT] = COMBO_ACTION(jspace_combo),
};

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

void process_combo_event(uint16_t combo_index, bool pressed) {
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

void activate_base_layer_combo(bool activated) {
    if (activated) {
        combo_enable();
    } else {
        combo_disable();
    }
}
