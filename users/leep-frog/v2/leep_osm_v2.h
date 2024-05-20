#pragma once

#ifdef LEEP_OSM_ENABLE

#include "quantum/leep/custom_osm_handlers.h"

#define OSM_CONFIG(keycode_value, activation_fn_value) { .keycode = keycode_value, .osm_step = OSM_NOOP, .osmed_key = 0, .osm_press_time = 0, .activation_fn = activation_fn_value }

extern leep_osm_config_t osm_configs[];

void OSM_handled(uint16_t keycode, bool pressed);
void OSM_cleanup(void);
void OSM_combo_cleanup(void);

#ifdef LEEP_TEST_MODE
bool OSM_test_check(char test_message[]);
#endif

#endif
