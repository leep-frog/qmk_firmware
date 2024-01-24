
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
#include "users/leep-frog/v2/leep_oneshot_v2.c"
#include "users/leep-frog/v2/leep_alt_v2.c"
#include "users/leep-frog/v2/leep_layers_v2.c"
#include "users/leep-frog/v2/leep_custom_keycodes_v2.c"
#include "users/leep-frog/v2/leep_osm_v2.c"


// TODO: #include "users/leep-frog/keyboard-main/leep_index_kb.c"
#include "users/leep-frog/keyboard-main/leep_combo_kb.c"
#include "users/leep-frog/keyboard-main/leep_tap_dance_kb.c"
#include "users/leep-frog/keyboard-main/leep_symbol_layer_overlap_kb.c"
#include "users/leep-frog/keyboard-main/leep_cr_desc_kb.c"
#include "users/leep-frog/keyboard-main/leep_to_ctrl_kb.c"
#include "users/leep-frog/main.c"

custom_unlocker_fn_t CustomUnlocker = &defaultUnlocker;
