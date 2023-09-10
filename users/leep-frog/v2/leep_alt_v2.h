#pragma once

extern uint16_t Alt_keycodes[];

extern const uint16_t AltLayer;
extern const uint16_t ToAltKeycode;

void ToAlt_handled(uint16_t keycode);
bool ToAlt_run(keyrecord_t *record, custom_keycode_value_t *_);

bool AltBlockProcessing(uint16_t keycode, keyrecord_t* record);

// Custom keycode handlers
bool AltTabHandler(keyrecord_t* record, custom_keycode_value_t *_);
bool AltShiftTabHandler(keyrecord_t* record, custom_keycode_value_t *_);
void AltLayerDeactivationHandler(bool activated);
