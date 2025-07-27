#pragma once

#include "leep_alt_v2.h"
#include "leep_layers_v2.h"
#include "keymap_introspection.h"


/****************
 * TO_ALT logic *
 ****************/

bool alt_tab_mode_active = false;

void _end_alt_tab_mode(void) {
  if (alt_tab_mode_active) {
    alt_tab_mode_active = false;
    unregister_code16(KC_RALT);
  }
}

void _start_alt_tab_mode(void) {
  if (!alt_tab_mode_active) {
    alt_tab_mode_active = true;
    register_code16(KC_RALT);
  }
}

bool AltBlockProcessing(uint16_t keycode, keyrecord_t* record) {
  if (!record->event.pressed) {
    return false;
  }

  // Only check if alt is active
  if (!alt_tab_mode_active) {
    return false;
  }

  for (int i = 0; i < Alt_keycodes_count(); i++) {
    if (keycode == Alt_keycodes_get(i)) {
      // It's a key that should proceed as normal
      return false;
    }
  }

  // Pressing a key to break the alt mode
  _end_alt_tab_mode();
  return true;
}

void AltLayerDeactivationHandler(bool activated) {
  if (!activated) {
    _end_alt_tab_mode();
  }
}

// The below functions implement custom keycode handlers

bool AltTabHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    _start_alt_tab_mode();
    register_code16(KC_TAB);
  } else {
    unregister_code16(KC_TAB);
  }

  return true;
}

bool AltShiftTabHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    _start_alt_tab_mode();
    register_code16(S(KC_TAB));
  } else {
    unregister_code16(S(KC_TAB));
  }

  return true;
}
