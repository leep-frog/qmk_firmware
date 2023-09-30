#pragma once

typedef void (*layer_change_fn_t) (bool activated);

#define MAX_NUM_LAYERS (sizeof(layer_state_t)*8)

extern layer_change_fn_t layer_handlers[];
extern bool layer_statuses[];

uint8_t LeepHighestLayer;

#define SET_LAYER_HANDLER(i, handler) layer_handlers[i] = &handler
