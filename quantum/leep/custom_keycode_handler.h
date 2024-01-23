#pragma once

typedef union {
uint16_t ck_int;
// TODO: Make this a pointer to save space?
char ck_string[30];
} custom_keycode_value_t;
typedef bool (*custom_keycode_fn_t) (keyrecord_t *record, custom_keycode_value_t *value);
typedef struct {
  custom_keycode_fn_t fn;
  custom_keycode_value_t v;
} custom_keycode_handler_t;
