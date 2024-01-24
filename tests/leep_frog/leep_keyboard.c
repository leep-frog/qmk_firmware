
#include "quantum.h"
#include "leep_keyboard.h"
#include "quantum/leep/custom_keycode_handler.h"

// TODO: #include "users/leep-frog/v2/leep_index_v2.c"
#include "users/leep-frog/v2/leep_tap_dance_v2.c"
#include "users/leep-frog/v2/leep_music_v2.c"
#include "users/leep-frog/v2/leep_record_v2.c"
#include "users/leep-frog/v2/leep_tap_dance_v2.c"
#include "users/leep-frog/v2/leep_shift_v2.c"
#include "users/leep-frog/v2/leep_color_v2.c"


// TODO: #include "users/leep-frog/keyboard-main/leep_index_kb.c"
#include "users/leep-frog/keyboard-main/leep_combo_kb.c"
#include "users/leep-frog/keyboard-main/leep_tap_dance_kb.c"

custom_keycode_handler_t custom_keycode_handlers[] = {};

uint16_t Alt_keycodes[] = {};

uint16_t OSM_shift_keycode = KC_1;

const uint16_t ToAltKeycode = KC_2;
const uint16_t ToCtrlKeycode = KC_3;
