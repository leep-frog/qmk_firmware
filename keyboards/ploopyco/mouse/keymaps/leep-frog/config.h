#pragma once

#undef LEEP_MAIN

#include "../../config.h"

#define MS_BTN1 KC_BTN1
#define MS_BTN2 KC_BTN2
#define MS_BTN3 KC_BTN3
#define MS_WHLU KC_WH_U
#define MS_WHLD KC_WH_D
#define MS_WHLL KC_WH_L
#define MS_WHLR KC_WH_R
#define MS_ACL0 KC_ACL0
#define MS_ACL1 KC_ACL1
#define MS_ACL2 KC_ACL2

// How long it takes for a tap to become a hold. Primarily added because
// Shift-combinations were too quick and causing a parentheses to be added.
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 180
// Allows us to define tapping term per key. See link for more details:
// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#tapping-term
#define TAPPING_TERM_PER_KEY

// Combo setup
// #define FORCE_NKRO
#define COMBO_TERM 40            // Number of milliseconds for combo keys.
#define COMBO_ONLY_FROM_LAYER 1  // Define all combos from the safe layer
// #define COMBO_SHOULD_TRIGGER
