#pragma once

#ifndef LEEP_WORKSPACE
#define LEEP_WORKSPACE

#define WS_RIGHT C(G(KC_RGHT))  // Slide to next workspace
#define WS_RGHT WS_RIGHT
#define WS_LEFT C(G(KC_LEFT))  // Slide to previous workspace
#define WS_BACK RGUI(KC_B)

#define WS_1 RCTL(RALT(RSFT(KC_1)))
#define WS_2 RCTL(RALT(RSFT(KC_2)))
#define WS_3 RCTL(RALT(RSFT(KC_3)))
#define WS_4 RCTL(RALT(RSFT(KC_4)))
#define WS_5 RCTL(RALT(RSFT(KC_5)))
#define WS_6 RCTL(RALT(RSFT(KC_6)))
#define WS_UP RCTL(RALT(KC_UP))
#define WS_DOWN RCTL(RALT(KC_DOWN))

// Layer swaps (see NAVIGATION layer).
#define MAIL_WS WS_1  // i key for inbox
#define CHAT_WS WS_2  // y for yap
#define CAL_WS WS_3   // m key for meetings
#define CODE_WS WS_4  // k for code
#define GIT_WS WS_5   // p for preview
#define MISC_WS WS_6  // ; cuz it's random

#endif
