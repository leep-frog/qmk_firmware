#pragma once

extern const uint16_t CtrlLayer;
extern const uint16_t ToCtrlKeycode;

void ToCtrl_handled(uint16_t keycode);
bool ToCtrl_run(keyrecord_t *record, uint16_t _);
