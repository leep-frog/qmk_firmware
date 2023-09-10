#pragma once

extern uint16_t Alt_keycodes[];

extern const uint16_t AltLayer;
extern const uint16_t ToAltKeycode;

void ToAlt_handled(uint16_t keycode);
void ToAlt_run(bool pressed);

bool AltBlockProcessing(uint16_t keycode, keyrecord_t* record);

// Custom keycode handlers
void AltLayerHandler(bool activated);
bool AltTabHandler(keyrecord_t* record);
bool AltShiftTabHandler(keyrecord_t* record);
void AltTabHandler_old(bool pressed);
void AltShiftTabHandler_old(bool pressed);
void AltLayerDeactivationHandler(bool activated);
