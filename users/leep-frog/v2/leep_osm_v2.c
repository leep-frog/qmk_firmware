#pragma once

#ifdef LEEP_OSM_ENABLE

#include "leep_osm_v2.h"
#include <stdio.h>


enum osm_enact_steps {
  OSM_NOOP,
  OSM_HOLD_CHECK,
  OSM_REGISTER_KEY,
  OSM_UNREGISTER_KEY,
  OSM_CLEANUP,
  OSM_RELEASE_ON_UNPRESS,
  OSM_HOLD,
};

static uint8_t osm_step = OSM_NOOP;
static uint16_t osmed_key = 0;

void OSM_deactivate(void) {
  layer_off(OSM_LAYER);
  unregister_code16(KC_RSFT);
  osm_step = OSM_NOOP;
}

void OSM_handled(uint16_t keycode, bool pressed) {
  switch (osm_step) {
  case OSM_NOOP:
    // Activate if pressing the relevant key
    if (pressed && keycode == OSM_shift_keycode) {
      layer_on(OSM_LAYER);
      register_code16(KC_RSFT);
      osm_step = OSM_HOLD_CHECK;
    }
    break;
  case OSM_HOLD_CHECK:
    // If we're pressing a different key first, then we are holding down the OSM key
    // in which case we simply need to release on unpress.
    if (pressed) {
      osm_step = OSM_RELEASE_ON_UNPRESS;

    // If we're unpressing the OSM key first, then we're going to register a key
    } else if /* Don't need this !pressed check since we use else-if against (pressed) (!pressed && */ (keycode == OSM_shift_keycode) {
      osm_step = OSM_REGISTER_KEY;
    }
    break;
  case OSM_RELEASE_ON_UNPRESS:
    if (!pressed && keycode == OSM_shift_keycode) {
      OSM_deactivate();
    }
    break;
  case OSM_REGISTER_KEY:
    if (pressed) {
      osmed_key = keycode;
      osm_step = OSM_UNREGISTER_KEY;
    }
    break;
  case OSM_UNREGISTER_KEY:
    // If we're pressing another key before we let go of the registered key, then remove shift immediately.
    if (pressed) {
      OSM_deactivate();

    // If we're unpressing the key that we registered with, then clean up OSM after the current loop is processed.
    } else if (/* !pressed && */ keycode == osmed_key) { // (!pressed not needed due to initial `if` before this `else-if`
      osm_step = OSM_CLEANUP;
    }
    break;
  case OSM_CLEANUP:
    // Handled by OSM_cleanup (which runs in the same loop, but after the key has been processed)
    break;
  }
}

void OSM_cleanup(void) {
  if (osm_step == OSM_CLEANUP) {
    OSM_deactivate();
  }
}

// Combo runs as single event (not press and unpress), so we need special logic to handle that.
void OSM_combo_cleanup(void) {
  if (osm_step == OSM_REGISTER_KEY) {
    OSM_deactivate();
  } else if (osm_step == OSM_HOLD_CHECK) {
    osm_step = OSM_RELEASE_ON_UNPRESS;
  }
}

#ifdef LEEP_TEST_MODE
bool OSM_test_check(char test_message[]) {
  if (osm_step != OSM_NOOP) {
    sprintf(test_message, "OSM isn't in defaualt state. Got %d; expected %d", osm_step, OSM_NOOP);
    return false;
  }
  return true;
}
#endif

#endif
