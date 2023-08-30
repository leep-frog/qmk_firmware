#pragma once

#include "leep_alt_v2.h"
#include "leep_layers_v2.h"
#include "keymap_introspection.h"

bool AltBlockProcessing(uint16_t keycode, keyrecord_t* record) {
  if (!record->event.pressed) {
    return false;
  }

  // Only check if alt is active
  if (!layer_statuses[AltLayer]) {
    return false;
  }

  for (int i = 0; i < Alt_keycodes_count(); i++) {
    if (keycode == Alt_keycodes_get(i)) {
      // It's a key that should proceed as normal
      return false;
    }
  }

  // Pressing a key to break the alt mode
  layer_off(AltLayer);
  return true;
}

void AltLayerHandler(bool activated) {
  if (activated) {
    writePinHigh(D4);
    register_code16(KC_RALT);
  } else {
    writePinLow(D4);
    unregister_code16(KC_RALT);
  }
}

// The below functions implement custom keycode handlers
bool AltTabHandler(keyrecord_t* record) {
  if (!record->event.pressed) {
    unregister_code16(KC_TAB);
    return true;
  }

  if (!layer_statuses[AltLayer]) {
    layer_on(AltLayer);
  }
  register_code16(KC_TAB);
  return true;
}

bool AltShiftTabHandler(keyrecord_t* record) {
  if (!record->event.pressed) {
    unregister_code16(S(KC_TAB));
    return true;
  }

  if (!layer_statuses[AltLayer]) {
    layer_on(AltLayer);
  }
  register_code16(S(KC_TAB));
  return true;
}
