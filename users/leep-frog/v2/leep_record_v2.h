#pragma once

#ifdef DYNAMIC_MACRO_ENABLE

#include "process_tap_dance.h"

// Implement tap_dance_user_fn_t
void Record1Function(tap_dance_state_t *state, void *user_data);
void Record2Function(tap_dance_state_t *state, void *user_data);
bool IsRecording(void);

#endif
