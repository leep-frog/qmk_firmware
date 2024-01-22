// Combos
enum combos {
    BD_RIGHT_CLICK,
    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM bd_combo[] = {KC_B, KC_D, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    // B+D = Right-click
    [BD_RIGHT_CLICK] = COMBO(bd_combo, KC_BTN2),
};
