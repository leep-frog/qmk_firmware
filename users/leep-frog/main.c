#ifdef LEEP_MAIN

void print_int(uint16_t k) {
  send_word(k);
}
#define PRINT_INT(i) print_int(i);

#include "./main.h"
#include <stdio.h>
#include "./v2/leep_index_v2.h"
#include "./keyboard-main/leep_index_kb.h"
#include "./v2/leep_index_v2.c"
#include "./keyboard-main/leep_index_kb.c"

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

#ifdef LEEP_TEST_MODE
char test_message[100] = "\0";

void test_confirm(keyrecord_t *record) {
  // ON press, set the message to a non-empty starting value
  if (record->event.pressed) {
    strcpy(test_message, "Running tests (waiting for release)...");
    return;
  }

  // OSM
  if (
    !OSM_test_check(test_message)
  ) {
    return;
  }

  if (LeepHighestLayer) {
    sprintf(test_message, "Expected to be in base layer, but was in layer %d", LeepHighestLayer);
    return;
  }

  // On release, run all verifications
  strcpy(test_message, "Success!");
  return;
}
#endif

bool _leep_keyboard_reset(keyrecord_t *record, custom_keycode_value_t *v) {
    if (record->event.pressed) {
      // Press
      LEEP_SOLID_COLOR(RED, true);
      SNG_RESET();
      #ifdef AUDIO_ENABLE
      while (is_playing_notes()) {
          wait_ms(75);
      }
      #endif
    } else {
      // Unpress (reset here so the color actually changes)
      reset_keyboard();
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

bool _slack_edit(keyrecord_t *record, custom_keycode_value_t *_) {
    if (record->event.pressed) {
      tap_code16(KC_MS_BTN2);
    } else {
      tap_code16(KC_E);
    }
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

bool _toggle_shift(keyrecord_t *record, custom_keycode_value_t *_) {
  // Toggle on unpress so we don't need to add extra keycode for toggle shift ignore
  if (!record->event.pressed) {
    ToggleShift();
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

static uint32_t oh_timer; // Only have one since left and right one-hand layers can't be active at the same time
void one_hand_layer_change(bool activated, char *press_key) {
  // Simple activation logic
  AltLayerDeactivationHandler(activated);
  if (activated) {
    leep_acl = 0;
    tap_code16(KC_ACL2);
  }

  // Logic to determine if simple modifier + key was intended (e.g. shift+F)
  if (activated) {
    oh_timer = timer_read();
  } else if (timer_elapsed32(oh_timer) < TAPPING_TERM) {
    // If the one-hand layer was activated and then deactivated very quickly
    // then likely was trying to just press the key with the modifier
    SEND_STRING(press_key);
  }
}

void left_hand_layer_change(bool activated) {
  one_hand_layer_change(activated, "/");
}

void right_hand_layer_change(bool activated) {
  one_hand_layer_change(activated, "4");
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
    UnsetShift();
    // Copy contents
    SEND_STRING(SS_COPY);
    // Delete selected text.
    SEND_STRING(SS_TAP(X_DELETE));
  }
  return false;
}

bool ck_noop(keyrecord_t *_k, custom_keycode_value_t *_c) { return false; }

#define CK_NOOP() CK_HANDLER_FN(ck_noop)

#define GCS_1 "cig"
#define GCS_2 "-cmwea"
#define GCS_3 "-prod"
#define GCS_4 "-1"

custom_keycode_handler_t custom_keycode_handlers[] = {
  // Fn handlers
  [TO_CTRL_HANDLER] = CK_HANDLER_FN(ToCtrl_run),
  [TO_CTLX_HANDLER] = CK_HANDLER_FN(to_ctrl_x_layer),
  [CTRL_W_HANDLER] = CK_HANDLER_FN(CtrlWHandler),
  [CK_WAIT_HANDLER] = CK_HANDLER_FN(_leep_wait),
  [CK_ATB_HANDLER] = CK_HANDLER_FN(AltTabHandler),
  [CK_SATB_HANDLER] = CK_HANDLER_FN(AltShiftTabHandler),
  [CK_ACL_HANDLER] = CK_HANDLER_FN(_change_mouse_speed),
  [CK_LOCK_HANDLER] = CK_HANDLER_FN(_leep_lock),
  [CK_RESET_HANDLER] = CK_HANDLER_FN(_leep_keyboard_reset),
  [KB_OFF_HANDLER] = CK_HANDLER_FN(_leep_keyboard_off),
  [CK_EYE_HANDLER] = CK_HANDLER_FN(_eye_care),
  [SLACK_EDIT_HANDLER] = CK_HANDLER_FN(_slack_edit),
  [MS_CTRL_HANDLER] = CK_HANDLER_FN(_ctrl_click),
  [CK_ALTT_HANDLER] = CK_HANDLER_FN(_alt_t_new),
  [CK_TGL_SHIFT_HANDLER] = CK_HANDLER_FN(_toggle_shift),
  [CK_MUTS_HANDLER] = CK_HANDLER_FN(MuteWithSound),
  [CK_MUT_HANDLER] = CK_HANDLER_FN(MuteWithoutSound),
  [CK_CTLG_HANDLER] = CK_HANDLER_FN(_ctrl_g_new),
  // String handlers
  [CK_UNBS_HANDLER] = CK_HANDLER_STRING(SS_RCTL(SS_TAP(X_BSPC))),
  [CK_LOGS_HANDLER] = CK_HANDLER_STRING(SS_TAP(X_ENTER) " | sort @timestamp ascy"),
  [URL_PST_HANDLER] = CK_HANDLER_STRING(NEW_TAB_STRING() SS_RSFT(SS_TAP(X_INSERT)) SS_TAP(X_ENTER)),
  [URL_CPY_HANDLER] = CK_HANDLER_STRING(FOCUS_TAB_STRING() SS_RCTL("c")),
  [OL_TDAY_HANDLER] = CK_HANDLER_STRING(OL_TDAY_STRING()),
  [CK_VERSION_HANDLER] = CK_HANDLER_STRING(LEEP_VERSION),
  [CK_DOWNLOAD_GCS] = CK_HANDLER_STRING(NEW_TAB_STRING() SS_RSFT(SS_TAP(X_INSERT)) SS_TAP(X_END) "?userProject=" GCS_1 GCS_2 GCS_3 GCS_4 SS_TAP(X_ENTER)),
  // Noops
  [CK_OSM_SHIFT_HANDLER] = CK_NOOP(), // Handled by leep_osm*.[ch] files
};

uint16_t Alt_keycodes[] = {
  CK_ATB,
  CK_SATB,
};

const uint16_t ToCtrlKeycode = TO_CTRL;

bool layers_status[NUM_LAYERS] = {
    [0]                    = true,
    [1 ... NUM_LAYERS - 1] = false,
};

#define LEEP_STARTUP_COLOR_MODE() LEEP_COLOR_MODE(GREEN, RGB_MATRIX_RAINDROPS, true)

SYMBOL_LAYER_OVERLAP_SETUP_FN_C(symbol_handler);
SYMBOL_LAYER_OVERLAP_SETUP_FN_C(alt_handler);

void keyboard_post_init_user(void) {
    if (!PlayedStartupSong()) {
        LEEP_STARTUP_COLOR_MODE();
    }

    // Add Layer handlers
    // Needed to undo SS_DOWN from [shift+]alt+tab logic (TD_ATAB/TD_STAB).
    SET_LAYER_HANDLER(LR_ALT, AltLayerDeactivationHandler);
    // Deactivate alt when exiting navigation layer.
    SET_LAYER_HANDLER(LR_NAVIGATION, AltLayerDeactivationHandler);
    // Left one-hand layer changes.
    SET_LAYER_HANDLER(LR_ONE_HAND_LEFT, left_hand_layer_change);
    // Right one-hand layer changes.
    SET_LAYER_HANDLER(LR_ONE_HAND_RIGHT, right_hand_layer_change);
    // Start/end ctrl-alt layer on layer on/off.
    SET_LAYER_HANDLER(LR_CTRL_ALT, ctrl_alt_layer);
    // Deactivate everything when going to safe layer.
    SET_LAYER_HANDLER(LR_ELLA, _ella_layer);
    SYMBOL_LAYER_OVERLAP_SETUP(symbol_handler);
    SYMBOL_LAYER_OVERLAP_SETUP(alt_handler);
}

#if defined(LEEP_UNLOCK_CODE)

uint8_t unlock_idx = 0;
const uint16_t unlock_code[] = LEEP_UNLOCK_CODE;
const uint8_t last_unlock_idx = sizeof(unlock_code) / sizeof(unlock_code[0]);

bool keyboardUnlocker(uint16_t keycode, keyrecord_t* record) {
  if (!record->event.pressed) {
    return false;
  }

  // This occurs if the keyboard was unlocked then relocked. This can be resolved
  // below, next to the LeepUnlock() call, but it remains here as safeguard for any
  // other ways (hopefully none) that would make unlock_idx larger than allowed.
  if (unlock_idx >= last_unlock_idx) {
    unlock_idx = 0;
  }

  uint16_t ella_keycode = keymap_key_to_keycode(LR_ELLA, record->event.key);

  if (ella_keycode != unlock_code[unlock_idx]) {
    unlock_idx = 0;
    // If it's also not the first key, then return; otherwise proceed.
    if (ella_keycode != unlock_code[unlock_idx]) {
      return false;
    }
  }

  if (++unlock_idx == last_unlock_idx) {
    LeepUnlock(false);
  }

  return false;
}

#elif defined(LEEP_NO_UNLOCK)

bool keyboardUnlocker(uint16_t keycode, keyrecord_t* record) {
  LeepUnlock(false);
  return true;
}

#else

bool keyboardUnlocker(uint16_t keycode, keyrecord_t* record) {
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

#endif



// Returns whether or not the key should be processed as normal or if we should just return
bool leep_startup_mode(uint16_t keycode, keyrecord_t* record) {
  if (PlayedStartupSong() || keycode == KB_OFF || keycode == CK_LOCK) {
    return true;
  }

  // Default to startup color mode in case keyboard isn't unlocked.
  LEEP_STARTUP_COLOR_MODE();

  return keyboardUnlocker(keycode, record);
}


void housekeeping_task_user(void) {
  OSM_cleanup();
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef LEEP_TEST_MODE
    // Don't do anything else if we press/unpress the CK_TEST key
    if (keycode == CK_TEST) {
      test_confirm(record);
      return false;
    }
#endif

    // Unlock keyboard (if relevant)
    if (!leep_startup_mode(keycode, record)) {
        return false;
    }

    OSM_handled(keycode, record->event.pressed);
    Mute_handled(record);
    if (CrDescProcessHandler(keycode, record->event.pressed) ||
            SymbolLayerOverlap_handled(&symbol_handler, keycode, record) ||
            SymbolLayerOverlap_handled(&alt_handler, keycode, record) ||
            AltBlockProcessing(keycode, record)) {
        return false;
    }
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
          UnsetShift();
        }
    }

    if (!process_custom_keycodes(keycode, record)) {
      return false;
    }

    return true;
}

#endif // LEEP_MAIN
