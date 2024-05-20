#pragma once

/************************************
* Required per-keyboard definitions *
************************************/

#define ENABLE_LEEP_COLOR
#define LEEP_SAFE_RANGE NEW_SAFE_RANGE
#define COMBO_ONLY_FROM_LAYER 1 // Ella layer
// How long it takes for a tap to become a hold. Primarily added because
// Shift-combinations were too quick and causing a parentheses to be added.
#define TAPPING_TERM 165

/***************
* Main include *
***************/

#include "users/leep-frog/keyboard-main/config.h"

/********************************
* Keyboard-specific definitions *
********************************/

#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
