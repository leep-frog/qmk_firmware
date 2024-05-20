// Combos

#ifdef COMBO_ENABLE
enum combos {
    DE_RIGHT_CLICK,
    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM de_combo[] = {KC_D, KC_E, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    // D+E = Right-click
    [DE_RIGHT_CLICK] = COMBO(de_combo, KC_BTN2),
};
#endif
