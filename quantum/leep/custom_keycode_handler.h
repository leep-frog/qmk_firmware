#pragma once

typedef union {
uint16_t ck_int;
// TODO: Make this a pointer to save space? Alternatively, make longer ones
// a function so we don't waste a bunch of space on other ones that only need
// short ones.
char ck_string[57];
} custom_keycode_value_t;
typedef bool (*custom_keycode_fn_t) (keyrecord_t *record, custom_keycode_value_t *value);
typedef struct {
  custom_keycode_fn_t fn;
  custom_keycode_value_t v;
} custom_keycode_handler_t;
