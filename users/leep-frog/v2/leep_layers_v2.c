#pragma once

#ifndef NUM_LAYERS
#    error Must define NUM_LAYERS (just make it the last enum in layer enum type)
#endif

bool layers_statuses[NUM_LAYERS] = {
    [0]                    = true,
    [1 ... NUM_LAYERS - 1] = false,
};

layer_state_t layer_state_set_user(layer_state_t state) {
  for (int i = 0; i < NUM_LAYERS; i++) {
    // If layer state changed
    bool current_state = layer_state_cmp(state, i);
    if (current_state != layers_statuses[i]) {
      // Update the layer status
      layers_statuses[i] = current_state;

      // Apply the layer handler (if present)

      // Note we don't do a size check on layer_handlers, because
      // we have to keep track of our own array sizes (https://stackoverflow.com/questions/9503098/sizeof-a-static-array-in-c)
      if (layer_handlers[i]) {
        layer_handlers[i](current_state);
      }
    }
  }
}
