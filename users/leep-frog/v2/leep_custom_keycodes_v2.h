#pragma once

#include "keymap_introspection.h"
#include "../../../quantum/action.h"
#include "./leep_url_v2.h"

#ifndef CUSTOM_KEYCODE_START
#define CUSTOM_KEYCODE_START SAFE_RANGE
#endif

bool process_custom_keycodes(uint16_t keycode, keyrecord_t* record);

// custom_keycode_fn_t defined in keymap_introspection.h

extern custom_keycode_handler_t custom_keycode_handlers[];

#define CK(i) CUSTOM_KEYCODE_START + i

// Use CK_HANDLER_STRING instead of this.
bool _ck_string_handler(keyrecord_t *record, custom_keycode_value_t *v);

#define CK_HANDLER_FN(handler) { .fn = &handler, .v = { .ck_int = 0 } }
#define CK_HANDLER_STRING(str) { .fn = &_ck_string_handler, .v = { .ck_string = str "\0" } }
#define CK_HANDLER_URL_STRING(str) { .fn = &_ck_url_string_handler, .v = { .ck_string = str "\0" } }
