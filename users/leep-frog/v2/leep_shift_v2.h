#pragma once

void ToggleShift(void);

bool UntoggleShift(void);

// TODO: Just make macro usable in tap dances
void TDToggleShift_hold(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);
void TDKillLine_finished(tap_dance_state_t *state, void *user_data);
void TDKillLine_reset(tap_dance_state_t *state, void *user_data);

void _ctrl_g_new(bool pressed);

bool IsShiftToggled(void);
