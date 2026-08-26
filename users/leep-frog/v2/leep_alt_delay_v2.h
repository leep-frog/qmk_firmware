#pragma once

// Delay (ms) inserted between registering the Alt modifier and sending the
// base keycode for Alt-modified keycodes (e.g. RALT(KC_A)). Override in
// config.h to tune for a specific remote desktop client.
#ifndef ALT_KEYCODE_DELAY_MS
#    define ALT_KEYCODE_DELAY_MS 20
#endif
