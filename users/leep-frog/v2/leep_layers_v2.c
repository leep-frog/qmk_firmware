#pragma once

#include "leep_layers_v2.h"

layer_change_fn_t layer_handlers[MAX_NUM_LAYERS] = {
    [0 ... MAX_NUM_LAYERS-1] = NULL,
};

// Max number of
bool layer_statuses[MAX_NUM_LAYERS] = {
    [0]                    = true,
    [1 ... MAX_NUM_LAYERS-1] = false,
};

uint8_t LeepHighestLayer = 0;


layer_state_t layer_state_set_user(layer_state_t state) {
  bool change = false;
  LeepHighestLayer = get_highest_layer(state);
  for (int i = 0; i < MAX_NUM_LAYERS; i++) {
    // If layer state changed
    bool current_state = layer_state_cmp(state, i);
    if (current_state != layer_statuses[i]) {
      change = true;
      // Update the layer status
      layer_statuses[i] = current_state;

      // Apply the layer handler (if present)
      // Note we don't do a size check on layer_handlers, because
      // we have to keep track of our own array sizes (https://stackoverflow.com/questions/9503098/sizeof-a-static-array-in-c)
      if (layer_handlers[i]) {
        layer_handlers[i](current_state);
      }
    }
  }

  if (change) {
      LEEP_LAYER_COLOR(LeepHighestLayer, false);
  }

  // Only want combos to be enabled in the base layer (even though we
  // define "COMBO_ONLY_FROM_LAYER 1", but we do that only so we can use the
  // simple keycodes defined in the safe layer).
  if (LeepHighestLayer == LR_BASE || LeepHighestLayer == LR_ELLA) {
    combo_enable();
  } else {
    combo_disable();
  }

  return state;
}
