#pragma once

#include "../../../../users/leep-frog/keyboard-main/config.h"

// #define LEEP_TEST_MODE
#define LEEP_KEYMAP_INTROSPECTION
#define LEEP_MAIN
#define LEEP_SAFE_RANGE SAFE_RANGE
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

#define MOONLANDER_USER_LEDS

// #include "../../config.h"
// #include "../../../../users/leep-frog/keyboard-main/config.h"

// Keyboard LED behavior was causing weird issues where layer changes would
// occur multiple times (including callbacks). Turning off system led logic
// (i.e. adding this define) seemed to resolve the issue.


// How long it takes for a tap to become a hold. Primarily added because
// Shift-combinations were too quick and causing a parentheses to be added.
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 150

#define DISABLE_RGB_MATRIX_SOLID_COLOR          // Static single hue, no speed support
#define DISABLE_RGB_MATRIX_ALPHAS_MODS          // Static dual hue, speed is hue for secondary hue
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN     // Static gradient top to bottom, speed controls how much gradient changes
#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT  // Static gradient left to right, speed controls how much gradient changes
// #define DISABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
#define DISABLE_RGB_MATRIX_BAND_SAT           // Single hue band fading saturation scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_VAL           // Single hue band fading brightness scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT  // Single hue 3 blade spinning pinwheel fades saturation
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL  // Single hue 3 blade spinning pinwheel fades brightness
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT    // Single hue spinning spiral fades saturation
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL    // Single hue spinning spiral fades brightness
#define DISABLE_RGB_MATRIX_CYCLE_ALL          // Full keyboard solid hue cycling through full gradient
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT   // Full gradient scrolling left to right
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN      // Full gradient scrolling top to bottom
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN       // Full gradient scrolling out to in
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL  // Full dual gradients scrolling out to in
// #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL  // Full gradient spinning pinwheel around center of keyboard
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL    // Full gradient spinning spiral around center of keyboard
#define DISABLE_RGB_MATRIX_DUAL_BEACON     // Full gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON  // Full tighter gradient spinning around center of keyboard
// #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // Full dual gradients spinning two halfs of keyboard
// #define DISABLE_RGB_MATRIX_RAINDROPS           // Randomly changes a single key's hue
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS        // Randomly changes a single key's hue and saturation
#define DISABLE_RGB_MATRIX_HUE_BREATHING              // Hue shifts up a slight ammount at the same time, then shifts back
#define DISABLE_RGB_MATRIX_HUE_PENDULUM               // Hue shifts up a slight ammount in a wave to the right, then back to the left
#define DISABLE_RGB_MATRIX_HUE_WAVE                   // Hue shifts up a slight ammount and then back down in a wave to the right
#define DISABLE_RGB_MATRIX_PIXEL_FRACTAL              // Single hue fractal filled keys pulsing horizontally out to edges
#define DISABLE_RGB_MATRIX_PIXEL_FLOW                 // Pulsing RGB flow along LED wiring with random hues
#define DISABLE_RGB_MATRIX_PIXEL_RAIN                 // Randomly light keys with random hues
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP             // How hot is your WPM!
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN               // That famous computer simulation
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE      // Pulses keys hit to hue & value then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE             // Static single hue, pulses keys hit to shifted hue then fades to current hue
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // Hue & value pulse near a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // Hue & value pulse near multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS       // Hue & value pulse the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS  // Hue & value pulse the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       // Hue & value pulse away on the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SPLASH                     // Full gradient & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_MULTISPLASH                // Full gradient & value pulse away from multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_SPLASH               // Hue & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
