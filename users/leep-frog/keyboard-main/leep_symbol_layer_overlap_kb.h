#pragma once

typedef struct {
    keypos_t first_symb_press_key;
    bool     first_symb_press;
    bool     resolved_first_symb_press;
    uint16_t layer;
    char    *keycode;
} layer_overlap_handler_t;

void SymbolLayerOverlap_reset(layer_overlap_handler_t *handler);
bool SymbolLayerOverlap_handled(layer_overlap_handler_t *handler, uint16_t keycode, keyrecord_t *record);

extern layer_overlap_handler_t symbol_handler;
extern layer_overlap_handler_t lr_left_handler;
extern layer_overlap_handler_t lr_right_handler;
