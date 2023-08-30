#pragma once

#define CK_UNDO CL(Z)

// Note: we use page down and page up because that works with chrome
// and "tab" is a special character in some terminals and sometimes gets
// modified or ignored when passed to processes inside of the terminal.
#define CK_TABF RCTL(KC_PGDN)    // Next tab in chrome (hold with shift for move tab)
#define CK_TABB LCTL(KC_PGUP)    // Previous tab in chrome (hold with shift for move tab)
#define CK_WWWF LALT(KC_RIGHT)   // Next page in chrome
#define CK_WWWB LALT(KC_LEFT)    // Previous page in chrome
#define CK_WWW_CLOSE RCTL(KC_W)
#define CK_WWW_NEW RCTL(KC_T)
#define CK_WWW_REOPEN RCTL(RSFT(KC_T))

// Mouse movements
#define MS_LEFT KC_MS_BTN1
#define MS_RGHT KC_MS_BTN2
#define MS_MID KC_MS_BTN3
#define MS_SMID RSFT(KC_MS_BTN3)

#define CK_NEW RCTL(RSFT(KC_N))

// Windows snip (screenshot)
#define CK_SNIP RGUI(RSFT(KC_S))

// Copy with ctrl+c (instead of ctrl+<insert>) so ctrl+c functionality
// still works (like cancelling in bash terminal).
#define CK_COPY RCTL(KC_C)
#define CK_PASTE RSFT(KC_INSERT)
#define CK_PSTE CK_PASTE

// These use IFTTT and use custom keyboard shortcuts under the hood.
#define LGHT_ON RCTL(RALT(RSFT(KC_8)))
#define LGHT_OF RCTL(RALT(RSFT(KC_9)))

#define SS_COPY SS_RCTL(SS_TAP(X_INSERT))
#define SS_PASTE SS_RSFT(SS_TAP(X_INSERT))
