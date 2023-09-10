#pragma once

extern const uint16_t CtrlLayer;
extern const uint16_t ToCtrlKeycode;

void ToCtrl_handled(uint16_t keycode);
void ToCtrl_run(bool pressed);
