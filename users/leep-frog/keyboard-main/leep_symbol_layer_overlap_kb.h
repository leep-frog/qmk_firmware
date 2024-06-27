#pragma once

typedef struct {
    keypos_t first_symb_press_key;
    bool     first_symb_press;
    uint32_t layer_active_at;
    bool     resolved_first_symb_press;
    bool     consider_hold;
    uint16_t layer;
    char    *keycode;
} layer_overlap_handler_t;

void SymbolLayerOverlap_reset(bool activated, layer_overlap_handler_t *handler);
bool SymbolLayerOverlap_handled(layer_overlap_handler_t *handler, uint16_t keycode, keyrecord_t *record);

extern layer_overlap_handler_t symbol_handler;
extern layer_overlap_handler_t lr_left_handler;
extern layer_overlap_handler_t lr_right_handler;

// Put the following in .h and .c files respectively
#define SYMBOL_LAYER_OVERLAP_SETUP_FN_H(handler) void symbol_layer_handler##handler(bool activated);
#define SYMBOL_LAYER_OVERLAP_SETUP_FN_C(handler) void symbol_layer_handler##handler(bool activated) { SymbolLayerOverlap_reset(activated, &handler); }


#define SYMBOL_LAYER_OVERLAP_SETUP(handler) SET_LAYER_HANDLER(handler.layer, symbol_layer_handler##handler)
