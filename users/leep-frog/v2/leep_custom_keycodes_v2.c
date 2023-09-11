#include "leep_custom_keycodes_v2.h"
#include "keymap_introspection.h"

// Use of keymap_introspection was inspired by the below commit, which removed the
// need for users to explicitly define combo count (and instead just infer it).
// https://github.com/qmk/qmk_firmware/commit/5faa23d54ca1e3ab83097f2a07922f48800616e6

bool process_custom_keycodes(uint16_t keycode, keyrecord_t* record) {
  if (keycode < CUSTOM_KEYCODE_START || keycode >= CUSTOM_KEYCODE_START + custom_keycode_handlers_count()) {
    return true;
  }

  uint16_t relative_keycode = keycode - CUSTOM_KEYCODE_START;
  custom_keycode_handler_t h = custom_keycode_handlers_get(relative_keycode);
  if (h.fn) {
    return h.fn(record, &h.v);
  }

  return true;
}

// Use CK_HANDLER_STRING instead of this.
bool _ck_string_handler(keyrecord_t *record, custom_keycode_value_t *v) {
  if (record->event.pressed) {
    send_string(v->ck_string);
  }
  return false;
}
