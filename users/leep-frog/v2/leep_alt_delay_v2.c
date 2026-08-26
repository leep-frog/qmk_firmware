#pragma once

#include "leep_alt_delay_v2.h"

// quantum.c's register_code16 registers the Alt modifier and sends the base
// keycode back-to-back. Some remote desktop clients (e.g. RDP) process the
// two HID reports too quickly and drop the modifier, so RALT(KC_A)/LALT(KC_A)
// style keycodes end up sending just "a" instead of the alted key. Overriding
// the (weak) register_code16 lets us pause after the modifier is registered,
// giving the remote client time to observe the modifier before the base key
// arrives.
extern uint8_t extract_mod_bits(uint16_t code);
extern void    do_code16(uint16_t code, void (*f)(uint8_t));

void register_code16(uint16_t code) {
  if (IS_MODIFIER_KEYCODE(code) || code == KC_NO) {
    do_code16(code, register_mods);
  } else {
    do_code16(code, register_weak_mods);
  }

  if (extract_mod_bits(code) & (MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_RIGHT_ALT))) {
    wait_ms(ALT_KEYCODE_DELAY_MS);
  }

  register_code(code);
}
