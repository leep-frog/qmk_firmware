#pragma once

// URLWait waits a short amount of time to allow the
// internet browser to run actions (like opening a new tab).
#define URLWait() wait_ms(80)

#define NEW_TAB()              \
    SEND_STRING(SS_RCTL("t")); \
    URLWait()

#define URL_COPY()                    \
    SEND_STRING(SS_DOWN(X_RCTL) "l"); \
    URLWait();                        \
    SNG_COPY();                       \
    SEND_STRING("c" SS_UP(X_RCTL))

#define URL_PASTE() \
    NEW_TAB();      \
    URLWait();      \
    SEND_STRING(SS_PASTE SS_TAP(X_ENTER));

#define NTH_URL_ID(k) SS_TAP(X_LEFT) REPEAT_##k(SS_TAP(X_RIGHT)) SS_RSFT(SS_TAP(X_RIGHT)) SS_UP(X_RCTL) SS_RSFT(SS_TAP(X_LEFT)) SS_DOWN(X_RCTL) "c"

// URL_ID gets the k-th word in the URL
#define URL_ID(k)              \
    SEND_STRING(SS_RCTL("l")); \
    URLWait();                 \
    SEND_STRING(SS_DOWN(X_RCTL) NTH_URL_ID(k) SS_RCTL("c"));

#define CR_ID() URL_ID(6)
