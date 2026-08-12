#include "../v2/leep_osm_v2.h"

static void shift_activation_fn(bool activated) {
  if (activated) {
    layer_on(LR_ELLA);
    register_code16(KC_RSFT);
  } else {
    layer_off(LR_ELLA);
    unregister_code16(KC_RSFT);
  }
}

static void emoji_activation_fn(bool activated) {
  if (activated) {
    layer_on(LR_EMOJI);
  } else {
    layer_off(LR_EMOJI);
  }
}

leep_osm_config_t osm_configs[2] = {
  OSM_CONFIG(CK_OSM_SHFT, shift_activation_fn),
  OSM_CONFIG(CK_OSM_EMOJI, emoji_activation_fn),
};
