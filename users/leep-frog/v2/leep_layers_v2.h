#pragma once

typedef union {
  uint16_t layer_int;
  // bool td_bool;
} layer_data_t;

typedef void (*layer_change_fn_t) (bool activated, layer_data_t *data);

#define MAX_NUM_LAYERS (sizeof(layer_state_t)*8)

extern layer_change_fn_t layer_handlers[];
extern layer_data_t layer_data[];
extern bool layer_statuses[];

extern uint8_t LeepHighestLayer;

#define SET_LAYER_HANDLER(i, handler) layer_handlers[i] = &handler
#define SET_LAYER_HANDLER_WITH_INT(i, handler, data) layer_handlers[i] = &handler; layer_data[i].layer_int = data
