#ifndef LEEP_MAIN
#define LEEP_MAIN

void print_int(int k) {
    char c[10];
    itoa(k, c, 10);
    send_string(c);
}
#define PRINT_INT(i) print_int(i);

#include <stdio.h>
#include "./keyboard-main/leep_index_kb.h"
#include "./v2/leep_index_v2.h"
// #include "interface.c"
// #include "enum.c"
// #include "./features/features.c"
// #include "color.c"
// #include "music.c"
// #include "google.c"
// #include "workspace.c"
// #include "url.c"
// #include "combo.c"
// #include "tap_dance.c"
// #include "record.c" included by tap_dance
// #include "shift.c"
// #include "ctrl.c"
// #include "slack.c"

// Note: wally sometimes crashes if the keyboard is plugged into the workstation,
// but behaves fine if the keyboard is plugged directly into the laptop.

#ifdef CONSOLE_ENABLE

#    define LEBUG(s, ...) uprintf(s, ##__VA_ARGS__);

#else

#    define LEBUG(s, ...)

#endif

void _ctrl_w_new(bool pressed) {
  if (!pressed) {
    return;
  }
  if (!IsShiftToggled()) {
    SEND_STRING(SS_RCTL("w"));
  } else {
    UntoggleShift();
    // Copy contents
    SEND_STRING(SS_COPY);
    // Delete selected text.
    SEND_STRING(SS_TAP(X_DELETE));
  }
}

void _leep_keyboard_off(bool pressed) {
    if (pressed) {
        LEEP_SOLID_COLOR(OFF, true);
        SetPlayedStartupSong(false);
    }
}

void _leep_lock(bool pressed) {
    if (pressed) {
        SEND_STRING(SS_LGUI("l"));
        _leep_keyboard_off(pressed);
    }
}

void _leep_wait(bool pressed) {
    if (pressed) {
        wait_ms(100);
    }
}

static int leep_acl = 0;

void _change_mouse_speed(bool pressed) {
    if (pressed) {
        // Default speed is fast, then medium, then slow (and reset on layer change)
        if (leep_acl == 0) {
            tap_code16(KC_ACL1);
        } else if (leep_acl == 1) {
            tap_code16(KC_ACL0);
        } else if (leep_acl == 2) {
            tap_code16(KC_ACL2);
        }
        leep_acl = (leep_acl + 1) % 3;
    }
}

void _alt_t_new(bool pressed) {
    if (!pressed) {
        return;
    }

    if (get_mods() & MOD_MASK_SHIFT) {
        // If holding shift, then actually send alt+shift+t
        // shift is already being held so we don't need to specify that here.
        // In fact, we shouldn't, otherwise we would un-tap the shift key, even
        // though it could still be held for more alt+shift keys.
        SEND_STRING(SS_RALT("t"));
    } else {
        // Otherwise, send new tab command (ctrl+shift+t)
        SEND_STRING(SS_RCTL(SS_RSFT("t")));
    }
}

void _ctrl_click(bool pressed) {
    if (!pressed) {
        return;
    }
    // Used to have the following line
    // #define MS_CTRL RCTL(KC_MS_BTN1)
    // but in my work Windows laptop, the ctrl and click would be too
    // close together and sometimes wouldn't work properly.
    SEND_STRING(SS_DOWN(X_RCTL));
    wait_ms(50);
    SEND_STRING(SS_TAP(X_MS_BTN1));
    SEND_STRING(SS_UP(X_RCTL));
}

void _eye_care(bool pressed) {
    if (pressed) {
        // The color change takes effect after the keycode is processed, so we can't
        // change the color twice in the _eye_care function.
        // Instead we set the first color on key down.
        LEEP_SOLID_COLOR(RED, false);
        SNG_EYE_START();
    } else {
        wait_ms(20 * 1000);
        LEEP_SOLID_COLOR(GREEN, false);
        SNG_EYE_END();
    }
}

static uint16_t ck_timer;

void _ck_timer(bool pressed) {
    if (pressed) {
        ck_timer = timer_read();
    } else {
        PRINT_INT(timer_elapsed(ck_timer));
    }
}

void to_ctrl_x_layer(bool pressed) {
    if (pressed) {
        SEND_STRING(SS_RCTL("x"));
        ActivateOneshot(LR_CTRL_X);
    }
}

void _ella_layer(bool activated) {
    if (!activated) {
        return;
    }

    if (IsShiftToggled()) {
        ToggleShift();
    }
    clear_mods();
}

#define KEY_PROCESSOR_OFFSET(v) C__OFFSET(CK_ENUM_START, v)

typedef void (*processor_action_t)(bool activated);

#define PRC_ACTION(user_fn) user_fn

#define C__OFFSET(C__START, v) v - C__START - 1

#define PROCESSOR_VALUE1(start, key, value) [C__OFFSET(start, key)] = value,
#define PROCESSOR_VALUE2(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE1(start, __VA_ARGS__)
#define PROCESSOR_VALUE3(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE2(start, __VA_ARGS__)
#define PROCESSOR_VALUE4(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE3(start, __VA_ARGS__)
#define PROCESSOR_VALUE5(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE4(start, __VA_ARGS__)
#define PROCESSOR_VALUE6(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE5(start, __VA_ARGS__)
#define PROCESSOR_VALUE7(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE6(start, __VA_ARGS__)
#define PROCESSOR_VALUE8(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE7(start, __VA_ARGS__)
#define PROCESSOR_VALUE9(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE8(start, __VA_ARGS__)
#define PROCESSOR_VALUE10(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE9(start, __VA_ARGS__)
#define PROCESSOR_VALUE11(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE10(start, __VA_ARGS__)
#define PROCESSOR_VALUE12(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE11(start, __VA_ARGS__)
#define PROCESSOR_VALUE13(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE12(start, __VA_ARGS__)
#define PROCESSOR_VALUE14(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE13(start, __VA_ARGS__)
#define PROCESSOR_VALUE15(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE14(start, __VA_ARGS__)
#define PROCESSOR_VALUE16(start, key, value, ...) PROCESSOR_VALUE1(start, key, value) PROCESSOR_VALUE15(start, __VA_ARGS__)

#define OPTIONAL_PROCESSOR_MACRO(_type_, sz, num_provided, e_start, prefix, suffix, dflt, ...) const _type_ PROGMEM prefix##_processors[sz] suffix = {[0 ... sz - 1] = dflt, PROCESSOR_VALUE##num_provided(e_start, __VA_ARGS__)};

#define PROCESSOR_MACRO(_type_, num, e_start, prefix, suffix, dflt, ...) OPTIONAL_PROCESSOR_MACRO(_type_, num, num, e_start, prefix, suffix, dflt, __VA_ARGS__)

#define PROCESSOR_MACRO_STRING(num, e_start, prefix, max_string_size, dflt, ...) PROCESSOR_MACRO(char, num, e_start, prefix, [max_string_size], dflt, __VA_ARGS__)

// Be sure to end each with "\0" character (string end character).

PROCESSOR_MACRO_STRING(4, CS_ENUM_START, cs, 26, "",
                       // KC_ESC actually sends a "`" (KC_GRAVE) character for some reason.
                       // Maybe it's something to do with KC_GESC overlapping or something?
                       // Who knows why, but we do need this custom keycode regardless to get around that.
                       CK_ESC, SS_TAP(X_ESC) "\0",
                       // Outlook today
                       OL_TDAY, SS_RALT(SS_TAP(X_H)) SS_TAP(X_O) SS_TAP(X_D) "\0",
                       // Universal backspace
                       CK_UNBS, SS_RCTL(SS_TAP(X_BSPC)) "\0",
                       // Log filter text
                       CK_LOGS, SS_TAP(X_ENTER) " | sort @timestamp asc\0"
                       // Trailing comma
)

PROCESSOR_MACRO_STRING(3, CU_ENUM_START, cu, 46, "",
                       // Copy URL
                       URL_COPY, "c",
                       // Copy URL ID
                       URL_ICP, SS_TAP(X_RIGHT) SS_RSFT(SS_TAP(X_LEFT)) "c",
                       // Copy URL CR ID
                       URL_CRI, NTH_URL_ID(6)
                       // Trailing comma
)

PROCESSOR_MACRO_STRING(3, CN_ENUM_START, cn, 12, "",
                       // Paste clipboard contents into the URL bar
                       URL_PST, SS_RSFT(SS_TAP(X_INSERT)) SS_TAP(X_ENTER),
                       // Open CL
                       CK_CL, "cl/" SS_TAP(X_ENTER),
                       // Open Moma
                       CK_MOMA, "moma " SS_TAP(X_ENTER)
                       // Trailing comma
)

PROCESSOR_MACRO(processor_action_t, 16, CK_ENUM_START, ck, , NULL,
                // Ctrl g
                CK_CTLG, &_ctrl_g_new,
                // Mute
                CK_MUT, &MuteWithoutSound,
                // Mute with Sound
                CK_MUTS, &MuteWithSound,
                // Alt-tab
                CK_ALTT, &_alt_t_new,
                // Ctrl-click
                MS_CTRL, &_ctrl_click,
                // Look away for 20 seconds
                CK_EYE, &_eye_care,
                // Keyboard off
                KB_OFF, &_leep_keyboard_off,
                // To the alt layer
                TO_ALT, &ToAlt_run,
                // To the ctrl layer
                TO_CTRL, &ToCtrl_run,
                // Lock the keyboard
                CK_LOCK, &_leep_lock,
                // Change the mouse speed
                CK_ACL, &_change_mouse_speed,
                // alt+tab
                CK_ATB, &AltTabHandler_old,
                // shift+alt+tab
                CK_SATB, &AltShiftTabHandler_old,
                // Wait for some milliseconds (useful for record).
                CK_WAIT, &_leep_wait,
                // Ctrl+w
                CTRL_W, &_ctrl_w_new,
                // To LR_CTRL_X
                TO_CTLX, &to_ctrl_x_layer
                // Trailing comma
)

void one_hand_layer_change(bool activated) {
  AltLayerDeactivationHandler(activated);
  if (activated) {
    leep_acl = 0;
    tap_code16(KC_ACL2);
  }
}

void ctrl_alt_layer(bool activated) {
    if (activated) {
        SEND_STRING(SS_DOWN(X_RCTL) SS_DOWN(X_RALT));
    } else {
        SEND_STRING(SS_UP(X_RCTL) SS_UP(X_RALT));
    }
}

OPTIONAL_PROCESSOR_MACRO(processor_action_t, NUM_LAYERS, 7, -1, layer, , NULL,
                         // Needed to undo SS_DOWN from [shift+]alt+tab logic (TD_ATAB/TD_STAB).
                         LR_ALT, &AltLayerDeactivationHandler,

                         // Only want combos to be enabled in the base layer (even though we
                         // define "COMBO_ONLY_FROM_LAYER 1", but we do that only so we can use the
                         // simple keycodes defined in the safe layer).
                         LR_BASE, &activate_base_layer_combo,
                         // Deactivate alt when exiting navigation layer.
                         LR_NAVIGATION, &AltLayerDeactivationHandler,
                         // Left one-hand layer changes.
                         LR_ONE_HAND_LEFT, &one_hand_layer_change,
                         // Right one-hand layer changes.
                         LR_ONE_HAND_RIGHT, &one_hand_layer_change,
                         // Start/end ctrl-alt layer on layer on/off.
                         LR_CTRL_ALT, &ctrl_alt_layer,
                         // Deactivate everything when going to safe layer.
                         LR_ELLA, &_ella_layer)

bool layers_status[NUM_LAYERS] = {
    [0]                    = true,
    [1 ... NUM_LAYERS - 1] = false,
};

#define LEEP_STARTUP_COLOR_MODE() LEEP_COLOR_MODE(GREEN, RGB_MATRIX_RAINDROPS, true)

void keyboard_post_init_user(void) {
    if (!PlayedStartupSong()) {
        LEEP_STARTUP_COLOR_MODE();
    }

    // Add Layer handlers
    // Needed to undo SS_DOWN from [shift+]alt+tab logic (TD_ATAB/TD_STAB).
    SET_LAYER_HANDLER(LR_ALT, AltLayerDeactivationHandler);
    // Only want combos to be enabled in the base layer (even though we
    // define "COMBO_ONLY_FROM_LAYER 1", but we do that only so we can use the
    // simple keycodes defined in the safe layer).
    SET_LAYER_HANDLER(LR_BASE, activate_base_layer_combo);
    // Deactivate alt when exiting navigation layer.
    SET_LAYER_HANDLER(LR_NAVIGATION, AltLayerDeactivationHandler);
    // Left one-hand layer changes.
    SET_LAYER_HANDLER(LR_ONE_HAND_LEFT, one_hand_layer_change);
    // Right one-hand layer changes.
    SET_LAYER_HANDLER(LR_ONE_HAND_RIGHT, one_hand_layer_change);
    // Start/end ctrl-alt layer on layer on/off.
    SET_LAYER_HANDLER(LR_CTRL_ALT, ctrl_alt_layer);
    // Deactivate everything when going to safe layer.
    SET_LAYER_HANDLER(LR_ELLA, _ella_layer);
}

// Returns whether or not the key should be processed as normal or if we should just return
bool leep_startup_mode(uint16_t keycode, keyrecord_t* record) {
    if (PlayedStartupSong() || keycode == KB_OFF || keycode == CK_LOCK) {
        return true;
    }

    if (record->event.pressed) {
        return false;
    }

    switch (keycode) {
        case KC_J:
        case KC_F:
            SNG_STARTUP();
            SetPlayedStartupSong(true);
            LEEP_LAYER_COLOR(LR_BASE, false);
            break;
        case KC_K:
        case KC_D:
            LeepMute();
            SetPlayedStartupSong(true);
            LEEP_LAYER_COLOR(LR_BASE, false);
            break;
        default:
            LEEP_STARTUP_COLOR_MODE();
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!leep_startup_mode(keycode, record)) {
        return false;
    }

    Mute_handled(record);
    if (SymbolLayerOverlap_handled(&symbol_handler, keycode, record) || SymbolLayerOverlap_handled(&lr_left_handler, keycode, record) || SymbolLayerOverlap_handled(&lr_right_handler, keycode, record) || AltBlockProcessing(keycode, record)) {
        return false;
    }
    ToAlt_handled(keycode);
    ToCtrl_handled(keycode);
    Oneshot_handled(record);

    // Return if this is being run on key un-pressed.
    if (!record->event.pressed) {
        // Run unpress events for custom keycodes
        switch (keycode) {
            case LEEP_ENUM_CASE(CK):
                if (ck_processors[LEEP_ENUM_OFFSET(CK, keycode)]) {
                    ck_processors[LEEP_ENUM_OFFSET(CK, keycode)](false);
                }
                return false;
        }

        return true;
    }

    // Untoggle shift the layer for all non-movement keys
    bool untoggle_shift = false;
    if (keycode >= CK_ENUM_START && keycode <= CK_ENUM_END) {
        switch (keycode) {
            case TO_ALT:
            case TO_CTRL:
            case CK_CTLG:
            case CTRL_W:
                break;
            default:
                untoggle_shift = true;
        }
    } else {
        switch (keycode & QK_BASIC_MAX) {
            case KC_HOME ... KC_UP:
                break;
            default:
                // Don't untoggle for ctrl g since that should *only* deactivate the shift layer
                // (and not send ctrl+g afterwards too)
                untoggle_shift = true;
        }
    }
    if (untoggle_shift) {
        UntoggleShift();
    }

    // We explicitly want all keycodes to return something to
    // 1) prevent custom keycodes from having logic in this switch and in run_array_processor
    // 2) prevent regular keycode logic from getting to custom keycodes (shouldn't actually be a problem but jic)
    switch (keycode) {
        case LEEP_ENUM_CASE(CS):
            send_string(cs_processors[LEEP_ENUM_OFFSET(CS, keycode)]);
            return false;
        case LEEP_ENUM_CASE(CU):
            SEND_STRING(SS_DOWN(X_RCTL) "l");
            URLWait();
            send_string(cu_processors[LEEP_ENUM_OFFSET(CU, keycode)]);
            SEND_STRING(SS_UP(X_RCTL));
            return false;
        case LEEP_ENUM_CASE(CN):
            NEW_TAB();
            send_string(cn_processors[LEEP_ENUM_OFFSET(CN, keycode)]);
            return false;
        case LEEP_ENUM_CASE(CK):
            if (ck_processors[LEEP_ENUM_OFFSET(CK, keycode)]) {
                ck_processors[LEEP_ENUM_OFFSET(CK, keycode)](true);
            }
            return false;
    }
    return true;
}

#endif
