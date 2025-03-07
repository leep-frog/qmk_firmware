#pragma once

// /************************************
// * Required per-keyboard definitions *
// ************************************/

// #define DISABLE_LEEP_COLOR
// #define LEEP_SAFE_RANGE SAFE_RANGE
// #define TAPPING_TERM 180

// #ifdef COMBO_ONLY_FROM_LAYER
//   #undef COMBO_ONLY_FROM_LAYER
//   // Ella layer
//   #define COMBO_ONLY_FROM_LAYER 1
// #endif

// Combo setup
#define COMBO_TERM 100            // Number of milliseconds for combo keys.
#define COMBO_VARIABLE_LEN
#define COMBO_ONLY_FROM_LAYER 1 // LR_ELLA

#define LEEP_MAIN
#define LEEP_KEYMAP_INTROSPECTION
#define LEEP_CUSTOM_LAYER_FN
