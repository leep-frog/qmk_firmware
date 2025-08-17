#pragma once

#include "quantum/keymap_introspection.h"
#include "quantum/leep/symbol_layer_overlap_handler.h"
#include "../v2/leep_layers_v2.h"

bool SymbolLayerOverlap_handled(uint16_t keycode, keyrecord_t *record);
void SymbolLayerOverlap_set_layer_handlers(void);
