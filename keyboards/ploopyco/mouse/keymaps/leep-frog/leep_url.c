#pragma once

void URLWait(void) { wait_ms(80); }

#define NEW_TAB()              \
    SEND_STRING(SS_RCTL("t")); \
    URLWait()

#define URL_COPY()                    \
    SEND_STRING(SS_DOWN(X_RCTL) "l"); \
    URLWait();                        \
    SEND_STRING("c" SS_UP(X_RCTL))

#define URL_PASTE() \
    NEW_TAB();      \
    URLWait();      \
    SEND_STRING(SS_PASTE SS_TAP(X_ENTER));
