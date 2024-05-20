#pragma once

extern const uint16_t CtrlLayer;
extern const uint16_t ToCtrlKeycode;

void ToCtrl_handled(uint16_t keycode);
bool ToCtrl_run(keyrecord_t *record, custom_keycode_value_t *_);
