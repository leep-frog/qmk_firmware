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
#include "../../../../../../../users/leep-frog/keyboard-main/leep_index_kb.c"
#include "./v2/leep_index_v2.h"

// Note: wally sometimes crashes if the keyboard is plugged into the workstation,
// but behaves fine if the keyboard is plugged directly into the laptop.

#ifdef CONSOLE_ENABLE

#    define LEBUG(s, ...) uprintf(s, ##__VA_ARGS__);

#else

#    define LEBUG(s, ...)

#endif

bool _leep_keyboard_off(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        LEEP_SOLID_COLOR(OFF, true);
        SetPlayedStartupSong(false);
    }
    return false;
}

bool _leep_lock(keyrecord_t *record, custom_keycode_value_t *v) {
    if (record->event.pressed) {
        SEND_STRING(SS_LGUI("l"));
        _leep_keyboard_off(record, v);
    }
    return false;
}

bool _leep_wait(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        wait_ms(100);
    }
    return false;
}

static int leep_acl = 0;

bool _change_mouse_speed(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
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
    return false;
}

bool _alt_t_new(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        return true;
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
    return false;
}

bool _ctrl_click(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        return true;
    }
    // Used to have the following line
    // #define MS_CTRL RCTL(KC_MS_BTN1)
    // but in my work Windows laptop, the ctrl and click would be too
    // close together and sometimes wouldn't work properly.
    SEND_STRING(SS_DOWN(X_RCTL));
    wait_ms(50);
    SEND_STRING(SS_TAP(X_MS_BTN1));
    SEND_STRING(SS_UP(X_RCTL));
    return false;
}

bool _eye_care(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
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
    return false;
}

static uint16_t ck_timer;

void _ck_timer(bool pressed) {
    if (pressed) {
        ck_timer = timer_read();
    } else {
        PRINT_INT(timer_elapsed(ck_timer));
    }
}

bool to_ctrl_x_layer(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
        SEND_STRING(SS_RCTL("x"));
        ActivateOneshot(LR_CTRL_X);
    }
    return false;
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

int layer_colors[NUM_LAYERS][3] = {
    [0 ... NUM_LAYERS - 1] =
        {//
         LEEP_C(GREEN)},
    // Base layer
    [LR_BASE] = {LEEP_C(CYAN)},
    // Ella layer
    [LR_ELLA] = {LEEP_C(GREEN)},
    // Ctrl layer
    [LR_CTRL] = {LEEP_C(SPRINGGREEN)},
    // Alt layer
    [LR_ALT] = {LEEP_C(MAGENTA)},
    // Ctrl+X layer
    [LR_CTRL_X] = {LEEP_C(CHARTREUSE)},
    // Ctrl+Alt layer
    [LR_CTRL_ALT] = {LEEP_C(GOLD)},
    // Nav layer
    [LR_NAVIGATION] = {LEEP_C(CORAL)},
    // Shortcut layer
    [LR_SHORTCUTS] = {LEEP_C(TURQUOISE)},
    // Symbol layer
    [LR_SYMB] = {LEEP_C(ORANGE)},
    // Outlook layer
    [LR_OUTLOOK] = {LEEP_C(BLUE)},
    // Scroll layer
    [LR_SCROLL] = {LEEP_C(RED)},
};

/*******************
 * Custom keycodes *
 *******************/

bool CtrlWHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (!record->event.pressed) {
    return true;
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
  return false;
}

// Note: we don't need to organize by handler type,
// but do so for readability.
enum custom_keycode_handlers {
  // Fn handlers
  TO_ALT_HANDLER,
  TO_CTRL_HANDLER,
  TO_CTLX_HANDLER,
  CTRL_W_HANDLER,
  CK_WAIT_HANDLER,
  CK_ATB_HANDLER,
  CK_SATB_HANDLER,
  CK_ACL_HANDLER,
  CK_LOCK_HANDLER,
  KB_OFF_HANDLER,
  CK_EYE_HANDLER,
  MS_CTRL_HANDLER,
  CK_ALTT_HANDLER,
  CK_MUTS_HANDLER,
  CK_MUT_HANDLER,
  CK_CTLG_HANDLER,
  CK_CRDC_HANDLER,
  // String handlers
  CK_UNBS_HANDLER,
  CK_LOGS_HANDLER,
  URL_PST_HANDLER,
  URL_CPY_HANDLER,
  OL_TDAY_HANDLER,
};

// bool nooooop(keyrecord_t *record, uint16_t v) { return false; }
custom_keycode_handler_t custom_keycode_handlers[] = {
  // Fn handlers
  [TO_ALT_HANDLER] = CK_HANDLER_FN(ToAlt_run),
  [TO_CTRL_HANDLER] = CK_HANDLER_FN(ToCtrl_run),
  [TO_CTLX_HANDLER] = CK_HANDLER_FN(to_ctrl_x_layer),
  [CTRL_W_HANDLER] = CK_HANDLER_FN(CtrlWHandler),
  [CK_WAIT_HANDLER] = CK_HANDLER_FN(_leep_wait),
  [CK_ATB_HANDLER] = CK_HANDLER_FN(AltTabHandler),
  [CK_SATB_HANDLER] = CK_HANDLER_FN(AltShiftTabHandler),
  [CK_ACL_HANDLER] = CK_HANDLER_FN(_change_mouse_speed),
  [CK_LOCK_HANDLER] = CK_HANDLER_FN(_leep_lock),
  [KB_OFF_HANDLER] = CK_HANDLER_FN(_leep_keyboard_off),
  [CK_EYE_HANDLER] = CK_HANDLER_FN(_eye_care),
  [MS_CTRL_HANDLER] = CK_HANDLER_FN(_ctrl_click),
  [CK_ALTT_HANDLER] = CK_HANDLER_FN(_alt_t_new),
  [CK_MUTS_HANDLER] = CK_HANDLER_FN(MuteWithSound),
  [CK_MUT_HANDLER] = CK_HANDLER_FN(MuteWithoutSound),
  [CK_CTLG_HANDLER] = CK_HANDLER_FN(_ctrl_g_new),
  [CK_CRDC_HANDLER] = CK_HANDLER_FN(CrDescHandler),
  // String handlers
  [CK_UNBS_HANDLER] = CK_HANDLER_STRING(SS_RCTL(SS_TAP(X_BSPC))),
  [CK_LOGS_HANDLER] = CK_HANDLER_STRING(SS_TAP(X_ENTER) " | sort @timestamp ascy"),
  [URL_PST_HANDLER] = CK_HANDLER_STRING(NEW_TAB_STRING() SS_RSFT(SS_TAP(X_INSERT)) SS_TAP(X_ENTER)),
  [URL_CPY_HANDLER] = CK_HANDLER_STRING(FOCUS_TAB_STRING() SS_RCTL("c")),
  [OL_TDAY_HANDLER] = CK_HANDLER_STRING(OL_TDAY_STRING()),
};

#define TO_ALT CK(TO_ALT_HANDLER)
#define TO_CTRL CK(TO_CTRL_HANDLER)
#define TO_CTLX CK(TO_CTLX_HANDLER)
#define CTRL_W CK(CTRL_W_HANDLER)
#define CK_WAIT CK(CK_WAIT_HANDLER)
#define CK_ATB CK(CK_ATB_HANDLER)
#define CK_SATB CK(CK_SATB_HANDLER)
#define CK_ACL CK(CK_ACL_HANDLER)
#define CK_LOCK CK(CK_LOCK_HANDLER)
#define KB_OFF CK(KB_OFF_HANDLER)
#define CK_EYE CK(CK_EYE_HANDLER)
#define MS_CTRL CK(MS_CTRL_HANDLER)
#define CK_ALTT CK(CK_ALTT_HANDLER)
#define CK_MUTS CK(CK_MUTS_HANDLER)
#define CK_MUT CK(CK_MUT_HANDLER)
#define CK_CTLG CK(CK_CTLG_HANDLER)
#define CK_CRDC CK(CK_CRDC_HANDLER)

#define URL_PST CK(URL_PST_HANDLER)
#define URL_CPY CK(URL_CPY_HANDLER)
#define OL_TDAY CK(OL_TDAY_HANDLER)
#define CK_UNBS CK(CK_UNBS_HANDLER)
#define CK_LOGS CK(CK_LOGS_HANDLER)

// TODO: Tap dance for this
#define URL_CRI _______

uint16_t Alt_keycodes[] = {
  CK_ATB,
  CK_SATB,
};

const uint16_t ToAltKeycode = TO_ALT;
const uint16_t ToCtrlKeycode = TO_CTRL;

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

// For some reason the `weak` modifier wasn't working, so went with this approach instead.
typedef bool (*custom_unlocker_fn_t) (uint16_t keycode, keyrecord_t *record);

bool defaultUnlocker(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CK_MCR1:
      case CK_MCR2:
        LeepUnlock(false);
        // Return true so macro behavior continues as normal
        return true;
    }
    return false;
  }

  switch (keycode) {
    case KC_J:
    case KC_F:
      LeepUnlock(true);
      break;
    case KC_K:
    case KC_D:
      LeepUnlock(false);
      break;
    default:
      LEEP_STARTUP_COLOR_MODE();
      break;
  }
  return false;
}

extern custom_unlocker_fn_t CustomUnlocker;

// Returns whether or not the key should be processed as normal or if we should just return
bool leep_startup_mode(uint16_t keycode, keyrecord_t* record) {
  if (PlayedStartupSong() || keycode == KB_OFF || keycode == CK_LOCK) {
    return true;
  }

  // Default to startup color mode in case keyboard isn't unlocked.
  LEEP_STARTUP_COLOR_MODE();

  if (CustomUnlocker) {
    return CustomUnlocker(keycode, record);
  }

  if (record->event.pressed) {
    SEND_STRING("No unlocker set");
  }
  return false;
}



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!leep_startup_mode(keycode, record)) {
        return false;
    }

    Mute_handled(record);
    if (CrDescProcessHandler(keycode, record) || SymbolLayerOverlap_handled(&symbol_handler, keycode, record) || SymbolLayerOverlap_handled(&lr_left_handler, keycode, record) || SymbolLayerOverlap_handled(&lr_right_handler, keycode, record) || AltBlockProcessing(keycode, record)) {
        return false;
    }
    ToAlt_handled(keycode);
    ToCtrl_handled(keycode);
    Oneshot_handled(record);

    switch (keycode) {
      // All non-movement keys don't untoggle
      // KC_HOME ... KC_UP includes KC_DELETE, so we just ignore that by
      // the following two lines:
      case KC_HOME ... (KC_DELETE - 1):
      case (KC_DELETE + 1) ... KC_UP:
      // Control with movement
      case LCTL(KC_HOME) ... LCTL(KC_DELETE - 1):
      case LCTL(KC_DELETE + 1) ... LCTL(KC_UP):
      case RCTL(KC_HOME) ... RCTL(KC_DELETE - 1):
      case RCTL(KC_DELETE + 1) ... RCTL(KC_UP):
      // Don't untoggle for ctrl g since that should *only* deactivate the shift layer
      // (and not send ctrl+g afterwards too)
      case CK_CTLG:
      // Don't untoggle for these layer changes
      case TO_CTRL:
      case TO_ALT:
        break;
      default:
        if (!IsToggleShiftTapDance(keycode)) {
          UntoggleShift();
        }
    }

    if (!process_custom_keycodes(keycode, record)) {
      return false;
    }

    return true;
}

#endif
