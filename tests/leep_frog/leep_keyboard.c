
#include "quantum.h"
#include "leep_keyboard.h"
#include "quantum/leep/custom_keycode_handler.h"
// #include "keymap_introspection.h"
// #include "../../../users/leep-frog/main.c"

combo_t key_combos[] = {};

tap_dance_action_t tap_dance_actions[] = {};

custom_keycode_handler_t custom_keycode_handlers[] = {};

uint16_t Alt_keycodes[] = {};

uint16_t OSM_shift_keycode = KC_1;

const uint16_t AltLayer = 123;
const uint16_t ToAltKeycode = KC_2;
const uint16_t ToCtrlKeycode = KC_3;
