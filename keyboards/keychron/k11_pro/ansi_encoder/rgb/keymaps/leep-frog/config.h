#pragma once

#include "../../../../users/leep-frog/keyboard-main/config.h"

// #define LEEP_TEST_MODE
#define LEEP_KEYMAP_INTROSPECTION
#define LEEP_MAIN
#define LEEP_SAFE_RANGE NEW_SAFE_RANGE
#define LEEP_OSM_ENABLE

#define FE_0(M, X)
#define FE_1(M, X) M(X)
#define FE_2(M, X, ...) M(X), FE_1(M, __VA_ARGS__)
#define FE_3(M, X, ...) M(X), FE_2(M, __VA_ARGS__)
#define FE_4(M, X, ...) M(X), FE_3(M, __VA_ARGS__)
#define FE_5(M, X, ...) M(X), FE_4(M, __VA_ARGS__)
#define FE_6(M, X, ...) M(X), FE_5(M, __VA_ARGS__)
#define FE_7(M, X, ...) M(X), FE_6(M, __VA_ARGS__)
#define FE_8(M, X, ...) M(X), FE_7(M, __VA_ARGS__)
#define FE_9(M, X, ...) M(X), FE_8(M, __VA_ARGS__)
#define FE_10(M, X, ...) M(X), FE_9(M, __VA_ARGS__)
#define FE_11(M, X, ...) M(X), FE_10(M, __VA_ARGS__)
#define FE_12(M, X, ...) M(X), FE_11(M, __VA_ARGS__)

#define REDUCE_0(M, SEP, X)
#define REDUCE_1(M, SEP, X) M(X)
#define REDUCE_2(M, SEP, X, ...) M(X) SEP REDUCE_1(M, SEP, __VA_ARGS__)
#define REDUCE_3(M, SEP, X, ...) M(X) SEP REDUCE_2(M, SEP, __VA_ARGS__)
#define REDUCE_4(M, SEP, X, ...) M(X) SEP REDUCE_3(M, SEP, __VA_ARGS__)
#define REDUCE_5(M, SEP, X, ...) M(X) SEP REDUCE_4(M, SEP, __VA_ARGS__)
#define REDUCE_6(M, SEP, X, ...) M(X) SEP REDUCE_5(M, SEP, __VA_ARGS__)
#define REDUCE_7(M, SEP, X, ...) M(X) SEP REDUCE_6(M, SEP, __VA_ARGS__)
#define REDUCE_8(M, SEP, X, ...) M(X) SEP REDUCE_7(M, SEP, __VA_ARGS__)
#define REDUCE_9(M, SEP, X, ...) M(X) SEP REDUCE_8(M, SEP, __VA_ARGS__)
#define REDUCE_10(M, SEP, X, ...) M(X) SEP REDUCE_9(M, SEP, __VA_ARGS__)
#define REDUCE_11(M, SEP, X, ...) M(X) SEP REDUCE_10(M, SEP, __VA_ARGS__)
#define REDUCE_12(M, SEP, X, ...) M(X) SEP REDUCE_11(M, SEP, __VA_ARGS__)

// Note: REPEAT_K does not separate with a comma, whereas FE does
#define REPEAT_0(X)
#define REPEAT_1(X) X
#define REPEAT_2(X) X REPEAT_1(X)
#define REPEAT_3(X) X REPEAT_2(X)
#define REPEAT_4(X) X REPEAT_3(X)
#define REPEAT_5(X) X REPEAT_4(X)
#define REPEAT_6(X) X REPEAT_5(X)
#define REPEAT_7(X) X REPEAT_6(X)
#define REPEAT_8(X) X REPEAT_7(X)
#define REPEAT_9(X) X REPEAT_8(X)
#define REPEAT_10(X) X REPEAT_9(X)
#define REPEAT_11(X) X REPEAT_10(X)

// How long it takes for a tap to become a hold. Primarily added because
// Shift-combinations were too quick and causing a parentheses to be added.
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 180

#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
