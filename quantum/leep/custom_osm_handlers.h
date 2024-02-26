#pragma once

typedef struct {
  uint16_t keycode;
  uint8_t osm_step;
  uint16_t osmed_key;
  uint16_t osm_press_time;
  void (*activation_fn)(bool);
} leep_osm_config_t;
