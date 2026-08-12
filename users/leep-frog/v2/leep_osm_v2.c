#pragma once

#ifdef LEEP_OSM_ENABLE

#include "leep_osm_v2.h"
#include <stdio.h>

enum osm_enact_steps {
  // Not in OSM mode at all
  OSM_NOOP,
  // The layer key has been pressed, waiting to see if we hold or release first
  OSM_HOLD_CHECK,
  // The layer key was pressed twice, which means we are in sticky mode (mod/layer is held down until pressed again)
  OSM_STICKY,
  // The osm key has been pressed once meaning the next key pressed should be with the osm mod/layer
  OSM_REGISTER_KEY,
  // The osm needs to be cleaned up
  OSM_CLEANUP,
  // The layer key is considered held down. Only deactivate the layer on unpress
  OSM_RELEASE_ON_UNPRESS,
};

const static uint16_t OSM_MAX_HOLD_TIME = TAPPING_TERM;
const static uint16_t OSM_MAX_WAIT_TIME = 10 * TAPPING_TERM;

void OSM_deactivate(leep_osm_config_t *osm_config) {
  if (osm_config->activation_fn) {
    osm_config->activation_fn(false);
  }
  osm_config->osm_step = OSM_NOOP;
}

void OSM_handled(uint16_t keycode, bool pressed) {
  for (uint8_t i = 0; i < osm_configs_count(); i++) {
    leep_osm_config_t *osm_config = osm_configs_get(i);
    switch (osm_config->osm_step) {
    case OSM_NOOP:
      // Activate if pressing the relevant key
      if (pressed && keycode == osm_config->keycode) {
        if (osm_config->activation_fn) {
          osm_config->activation_fn(true);
        }
        osm_config->osm_step = OSM_HOLD_CHECK;
        osm_config->osm_press_time = timer_read();
      }
      break;
    case OSM_HOLD_CHECK:
      // If we're pressing a different key first, then we are holding down the OSM key
      // in which case we simply need to release on unpress.
      if (pressed) {
        osm_config->osm_step = OSM_RELEASE_ON_UNPRESS;

      // If we're unpressing the OSM key first, then we're going to register a key
      } else if /* Don't need this !pressed check since we use else-if against (pressed) (!pressed && */ (keycode == osm_config->keycode) {

        // If held too long, then do nothing
        if (timer_elapsed(osm_config->osm_press_time) > OSM_MAX_HOLD_TIME) {
          OSM_deactivate(osm_config);
        } else {
          osm_config->osm_step = OSM_REGISTER_KEY;
        }
      }
      break;
    case OSM_RELEASE_ON_UNPRESS:
      if (!pressed && keycode == osm_config->keycode) {
        OSM_deactivate(osm_config);
      }
      break;
    case OSM_REGISTER_KEY:
      // Note: we need to clean-up right away, primarily because pressing a key in one layer,
      // and then unpressing it another, when one of the keys in a layer is a tap dance and the other is not
      // (e.g. KC_A in LR_ELLA and TD_A in LR_BASE) causes strange behavior (basically, QMK doesn't track
      // that state properly for tap dance keys).
      //
      // I looked into the issue for a while, but it's above my open source paygrade, and just releasing
      // shift right away covers all our use cases as well.
      if (pressed) {
        if (keycode == osm_config->keycode) {
          osm_config->osm_step = OSM_STICKY;
        } else {
          osm_config->osmed_key = keycode;
          osm_config->osm_step = OSM_CLEANUP;
        }
      }
      break;
    case OSM_STICKY:
      if (pressed && keycode == osm_config->keycode) {
        OSM_deactivate(osm_config);
      }
      break;
    // case OSM_CLEANUP: // Handled by OSM_cleanup (which runs in the same loop, but after the key has been processed)
    }
  }
}

void OSM_cleanup(void) {
  for (uint8_t i = 0; i < osm_configs_count(); i++) {
    leep_osm_config_t *osm_config = osm_configs_get(i);
    bool pressed_long_ago = osm_config->osm_step == OSM_REGISTER_KEY && timer_elapsed(osm_config->osm_press_time) > OSM_MAX_WAIT_TIME;
    if (pressed_long_ago || osm_config->osm_step == OSM_CLEANUP) {
      OSM_deactivate(osm_config);
    }
  }
}

// Combo runs as single event (not press and unpress), so we need special logic to handle that.
void OSM_combo_cleanup(void) {
  for (uint8_t i = 0; i < osm_configs_count(); i++) {
    leep_osm_config_t *osm_config = osm_configs_get(i);
    if (osm_config->osm_step == OSM_REGISTER_KEY) {
      OSM_deactivate(osm_config);
    } else if (osm_config->osm_step == OSM_HOLD_CHECK) {
      osm_config->osm_step = OSM_RELEASE_ON_UNPRESS;
    }
  }
}

#ifdef LEEP_TEST_MODE
bool OSM_test_check(char test_message[]) {
  for (uint8_t i = 0; i < osm_configs_count(); i++) {
    leep_osm_config_t *osm_config = osm_configs_get(i);
    if (osm_config->osm_step != OSM_NOOP) {
      sprintf(test_message, "OSM isn't in defaualt state. Got %d; expected %d", osm_config->osm_step, OSM_NOOP);
      return false;
    }
  }
  return true;
}
#endif

#endif
