#pragma once

typedef struct {
  // Constant fields
  const uint16_t layer;
  const uint32_t keycode;
  const uint32_t osm_keycode;

  // Changing fields
  uint32_t first_symb_press_keycode;
  keypos_t first_symb_press_key_pos;
  bool     first_symb_press;
  bool     resolved_first_symb_press;

  uint32_t key_press_at;
  uint32_t key_in_layer_duration;
} layer_overlap_handler_t;
