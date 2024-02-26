
/************************************
* Required per-keyboard definitions *
************************************/

#ifndef LEEP_SAFE_RANGE
  #error "Must define LEEP_SAFE_RANGE in keyboard's config.h file"
#endif

#ifndef COMBO_ONLY_FROM_LAYER
  #error "Must define COMBO_ONLY_FROM_LAYER in keyboard's config.h file"
#endif

#ifndef TAPPING_TERM
  #error "Must define TAPPING_TERM in keyboard's config.h file"
#endif

// Explicitly set ENABLE_LEEP_COLOR or DISABLE_LEEP_COLOR
#ifndef ENABLE_LEEP_COLOR
  #ifndef DISABLE_LEEP_COLOR
    #error "Either ENABLE_LEEP_COLOR or DISABLE_LEEP_COLOR must be set"
  #endif
#endif

#ifdef ENABLE_LEEP_COLOR
  #ifdef DISABLE_LEEP_COLOR
    #error "Not allowed to set both ENABLE_LEEP_COLOR and DISABLE_LEEP_COLOR"
  #endif
#endif

/************************
* Feature configuration *
************************/

// Use these two values to determine whether main logic is used.
#define LEEP_KEYMAP_INTROSPECTION
#define LEEP_MAIN
#define LEEP_OSM_ENABLE

// Allows us to define tapping term per key. See link for more details:
// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#tapping-term
#define TAPPING_TERM_PER_KEY

// Combo setup
// #define FORCE_NKRO
#define COMBO_TERM 40            // Number of milliseconds for combo keys.
#define COMBO_SHOULD_TRIGGER
#define COMBO_VARIABLE_LEN



// Override built-ins:
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_audio.md#songs
// We define our own start-up song (see SNG_STARTUP)
// so we can add logic that allows for disabling it from being played.
#define STARTUP_SONG SONG()
#define GOODBYE_SONG SONG()

// MOUSE CURSOR

// These values are set in the moonlander config.h, so we need to override them
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_MOVE_DELTA
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_TIME_TO_MAX

#define MK_3_SPEED
// #define MK_MOMENTARY_ACCEL // Leaving this out uses tap-to-select mode

// Delay between pressing a movement key and cursor movement
#define MOUSEKEY_DELAY 0
// Time between cursor movements in milliseconds
#define MOUSEKEY_INTERVAL 16
// Step size
#define MOUSEKEY_MOVE_DELTA 4
// Maximum cursor speed at which acceleration stops
#define MOUSEKEY_MAX_SPEED 10
// Time until maximum cursor speed is reached
#define MOUSEKEY_TIME_TO_MAX 0

// #define MK_C_INTERVAL_0 6  // Default value is 32
// #define MK_C_INTERVAL_1 4  // Default value is 16
#define MK_C_OFFSET_0 2  // Default is 1
#define MK_C_OFFSET_1 5  // Default is 4
#define MK_C_OFFSET_2 10

// Oneshot
// https://github.com/qmk/qmk_firmware/blob/master/docs/one_shot_keys.md

// Tapping a one shot key this number of times holds the key until tapped once again.
#define ONESHOT_TAP_TOGGLE 2
// Time (in ms) before the one shot key is released.
#define ONESHOT_TIMEOUT 500


/****************
* Helper macros *
*****************/

// TODO: Remove this and use REDUCE_N instead
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
#define REDUCE_N(N, M, SEP, ...) REDUCE##N(M, SEP, __VA_ARGS__)

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
