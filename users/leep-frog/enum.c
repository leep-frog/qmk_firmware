#ifndef LEEP_ENUMS
#define LEEP_ENUMS

enum layers { // prefix LR
    // Default layer
    LR_BASE,
    // The safe layer needs to stay in this position because this is the layer
    // from which we define combos (see 'COMBO_ONLY_FROM_LAYER 1' in config.h).
    LR_ELLA,
    LR_CTRL,
    LR_ALT,
    LR_SYMB,       // symbols
    LR_CTRL_X,     // layer activated temporarily after hitting x in the CTRL layer.
    LR_SHORTCUTS,  // command for combination keystrokes.
    LR_NAVIGATION, // command for changing workspaces.
    LR_OUTLOOK,
    LR_CTRL_ALT,
    LR_ONE_HAND_LEFT,
    LR_ONE_HAND_RIGHT,
    LR_SCROLL,

    NUM_LAYERS,
};

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md#defining-lighting-layers-iddefining-lighting-layers
#ifdef RGBLIGHT_MAX_LAYERS
#    undef RGBLIGHT_MAX_LAYERS
#endif
#define RGBLIGHT_MAX_LAYERS NUM_LAYERS

enum td_keys { // prefix TDK
    TDK_SHIFT_TOGGLE,
    TDK_KILL_LINE,
    TDK_MACRO_1,
    TDK_MACRO_2,
    TDK_BACKSPACE,
    TDK_DELETE,
    TDK_MARKDOWN_PASTE,
    TDK_OUTLOOK_RELOAD,
    TDK_RESET,
    TDK_A,
    TDK_B,
    TDK_C,
    TDK_I,
    TDK_U,
    TDK_V,
    TDK_Y,
    TDK_SHIFT_LAYER,
    TDK_SYMB_LAYER,
    // One hand keys
    TDK_OH_COPY,
    TDK_OH_PASTE,
    TDK_CTL_T,
    TDK_SCROLL_LEFT,
    TDK_SCROLL_RIGHT,
    TDK_TO_OUTLOOK,
    TDK_TO_NAV,
    TDK_TO_NAV_RCBR,
    TDK_TO_SHORTCUT,
    TDK_ELLA_MODE,
};

// Custom keycode enums
#define LEEP_ENUM(name, prefix, start, ...) \
    enum name {                             \
        prefix##_ENUM_START = start - 1,    \
        __VA_ARGS__ prefix##_ENUM_END,      \
    };

#define LEEP_ENUM_OFFSET(prefix, v) v - prefix##_ENUM_START - 1

#define LEEP_ENUM_CASE(prefix) prefix##_ENUM_START + 1 ... prefix##_ENUM_END - 1

LEEP_ENUM(custom_strings, CS, LEEP_SAFE_RANGE + 1,
          // Universal backspace
          CK_UNBS,
          // Outlook today
          OL_TDAY,
          // Escape
          CK_ESC,
          // Log filter text
          CK_LOGS,
          // Trailing comma: linter moves close paren to end of previous line;
          // these lines prevent that and act as trailing comma for better diffs.
)

LEEP_ENUM(custom_url_strings, CU, CS_ENUM_END,
          // Copy URL from a Chrome browser
          URL_COPY,
          // Copy URL ID
          URL_ICP,
          // Get the CR ID from the URL
          URL_CRI,
          // Trailing comma
)

LEEP_ENUM(custom_new_tab_strings, CN, CU_ENUM_END,
          // Paste URL
          URL_PST,
          // Open critique
          CK_CL,
          // Open moma
          CK_MOMA,
          // Trailing comma
)

LEEP_ENUM(custom_keycodes, CK, CN_ENUM_END,
          // Ctrl+g
          CK_CTLG,
          // Alt tab
          CK_ALTT,
          // Mute codes
          CK_MUT, CK_MUTS,
          // Mouse control click
          MS_CTRL,
          // Eye care
          CK_EYE,
          // To alt layer
          TO_ALT,
          // To ctrl layer
          TO_CTRL,
          // Lock keyboard and keyboard off
          CK_LOCK, KB_OFF,
          // Switches mouse acceleration
          CK_ACL,
          // Useful for waiting during macro recording/playback.
          CK_WAIT,
          // alt+tab
          CK_ATB,
          // shift+alt+tab
          CK_SATB,
          // To LR_CTRL_X
          TO_CTLX,
          // Trailing comma
)

// Layer toggling
// Defined here because needed by combo.c
#define TO_ELLA TO(LR_ELLA)
#define TO_CTAL MO(LR_CTRL_ALT)

#endif
