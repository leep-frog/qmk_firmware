#pragma once

#ifdef LEEP_OSM_ENABLE

extern const uint16_t OSM_shift_keycode;

void OSM_handled(uint16_t keycode, bool pressed);
void OSM_cleanup(void);
void OSM_combo_cleanup(void);

#ifdef LEEP_TEST_MODE
bool OSM_test_check(char test_message[]);
#endif

#endif
