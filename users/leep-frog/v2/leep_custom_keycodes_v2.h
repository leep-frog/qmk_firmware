#pragma once

#include "keymap_introspection.h"
#include "../../../quantum/action.h"

#ifndef CUSTOM_KEYCODE_START
#define CUSTOM_KEYCODE_START SAFE_RANGE
#endif

bool process_custom_keycodes(uint16_t keycode, keyrecord_t* record);

// custom_keycode_fn_t defined in keymap_introspection.h

extern custom_keycode_handler_t custom_keycode_handlers[];

#define CK(i) CUSTOM_KEYCODE_START + i

#define CK_HANDLER_FN(handler) { .fn = &handler, .v = 0 }
