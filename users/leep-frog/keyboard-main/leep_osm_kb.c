#include "../v2/leep_osm_v2.h"

void shift_activation_fn(bool activated) {
  if (activated) {
    layer_on(OSM_LAYER);
    register_code16(KC_RSFT);
  } else {
    layer_off(OSM_LAYER);
    unregister_code16(KC_RSFT);
  }
}

leep_osm_config_t osm_configs[1] = {
  OSM_CONFIG(CK_SHFT, shift_activation_fn),
};
