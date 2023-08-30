#pragma once

#include "leep_alt_v2.h"
#include "keymap_introspection.h"

bool leep_alt_pressed = false;

bool Alt_is_active(void) {
    return leep_alt_pressed;
}

bool Alt_block_processing(uint16_t keycode) {
  // Only check if alt is active
  if (!Alt_is_active()) {
    return false;
  }

  for (int i = 0; i < Alt_keycodes_count(); i++) {
    if (keycode == Alt_keycodes_get(i)) {
      // It's a key that should proceed as normal
      return false;
    }
  }

  // Pressing a key to break the alt mode
  Alt_deactivate();
  return true;
}

void Alt_activate(void) {
    leep_alt_pressed = true;
    register_code16(KC_RALT);
}

void Alt_deactivate(void) {
    leep_alt_pressed = false;
    unregister_code16(KC_RALT);
}

// The below functions implement custom handlers
bool AltTabHandler(keyrecord_t* record) {
  if (!record->event.pressed) {
    unregister_code16(KC_TAB);
    return true;
  }

  Alt_activate();
  register_code16(KC_TAB);
  return true;
}

bool AltShiftTabHandler(keyrecord_t* record) {
  if (!record->event.pressed) {
    unregister_code16(S(KC_TAB));
    return true;
  }

  Alt_activate();
  register_code16(S(KC_TAB));
  return true;
}
