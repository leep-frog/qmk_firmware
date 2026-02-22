#pragma once

enum layers {
    LR_BASE,
    #ifdef COMBO_ENABLE
    LR_SAFE,
    #endif
    LR_CTRL,
    LR_ALT,
    LR_WS,
    LR_ONSHAPE,
    NUM_LAYERS,
};

enum dances {
    TDK_ALT,
    TDK_CTRL,
    TDK_CTRL_TAB,
    TDK_CTRL_STAB,
    TDK_WORKSPACE,
    TDK_COPY_PASTE,
    TDK_REOPEN_RELOAD_TAB,
    TDK_WIN_TAB,
    TDK_PRINT_SCREEN,
    // TDK_OUTLOOK_DELETE,
    // TDK_OUTLOOK_RELOAD,
    // TDK_OUTLOOK_READ,
    // TDK_VSCODE_DEFINITION,
    TDK_BOOT,
};

enum custom_keycodes {
    START = SAFE_RANGE,
    CK_ATAB,
    CK_SATAB,
    CK_1OR2,
};
