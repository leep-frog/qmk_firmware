#pragma once

#include "../../config.h"
#include "../../../../../../../users/leep-frog/keyboard-main/config.h"

// How long it takes for a tap to become a hold. Primarily added because
// Shift-combinations were too quick and causing a parentheses to be added.
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 180

#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
