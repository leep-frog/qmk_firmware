#pragma once

#include "users/leep-frog/main.h" // Needed for TO_SYMB

// Combos
enum combos {
    JI_ESC,
    JK_HYPHEN,
    JL_EQUALS,
    // KL_ENTER,
    DF_QUOTE,
    SD_TICK,
    FSHIFT_OH_LEFT,
    JSPACE_OH_RIGHT,
    // J_SEMICLN is still available,
    // SF is still an available combo slot.
    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM ji_combo[] = {KC_J, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_L, KC_J, COMBO_END};
// const uint16_t PROGMEM kl_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM fshift_combo[] = {KC_F, KC_RSFT, COMBO_END};
const uint16_t PROGMEM jspace_combo[] = {KC_J, TO_SYMB, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    // J+I = Escape
    [JI_ESC] = COMBO(ji_combo, KC_ESCAPE),
    // J+K = Hyphen
    [JK_HYPHEN] = COMBO(jk_combo, KC_MINUS),
    // J+L = Equals
    [JL_EQUALS] = COMBO(jl_combo, KC_EQUAL),
    // K+L = Enter TODO: Change to something else useful?
    // [KL_ENTER] = COMBO(kl_combo, KC_ENTER),
    // D+F = Quote
    [DF_QUOTE] = COMBO_ACTION(df_combo),
    // S+D = Tick (`)
    [SD_TICK] = COMBO(sd_combo, KC_GRAVE),
    // F+Enter = LH layer
    [FSHIFT_OH_LEFT] = COMBO_ACTION(fshift_combo),
    // J+Space = RH layer
    [JSPACE_OH_RIGHT] = COMBO_ACTION(jspace_combo),
};
