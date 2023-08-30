#pragma once

extern uint16_t Alt_keycodes[];

extern const uint16_t AltLayer;

bool AltBlockProcessing(uint16_t keycode, keyrecord_t* record);

// Custom keycode handlers
void AltLayerHandler(bool activated);
bool AltTabHandler(keyrecord_t* record);
bool AltShiftTabHandler(keyrecord_t* record);
