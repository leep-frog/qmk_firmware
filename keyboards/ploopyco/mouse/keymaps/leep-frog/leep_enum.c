#pragma once

enum layers {
    LR_BASE,
    LR_SAFE,
    LR_CTRL,
    LR_ALT,
    LR_WS,
    LR_KB,
    LR_POWER_KB,
    LR_OUTLOOK,
    NUM_LAYERS,
};

enum dances {
    TDK_ALT,
    TDK_CTRL,
    TDK_CTRL_TAB,
    TDK_CTRL_STAB,
    TDK_WORKSPACE,
    TDK_COPY,
    TDK_PASTE,
    TDK_OPEN_TAB,
    TDK_CLOSE_TAB,
    TDK_OUTLOOK_DELETE,
    TDK_OUTLOOK_RELOAD,
    TDK_OUTLOOK_READ,
    TDK_VSCODE_DEFINITION,
    TDK_BOOT,
};

enum custom_keycodes {
    START = SAFE_RANGE,
    CK_ATAB,
    CK_SATAB,
    OL_TDAY,
};
