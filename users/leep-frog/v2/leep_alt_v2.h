#pragma once

extern uint16_t Alt_keycodes[];

bool Alt_is_active(void);
void Alt_activate(void);
void Alt_deactivate(void);
bool Alt_block_processing(uint16_t keycode);

// Custom keycode handlers
bool AltTabHandler(keyrecord_t* record);
bool AltShiftTabHandler(keyrecord_t* record);
