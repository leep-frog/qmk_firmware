#pragma once

void ToggleShift(void);

bool UntoggleShift(void);

// TODO: Just make macro usable in tap dances
void TDToggleShift_hold(tap_dance_state_t *state, bool finished, leep_td_value_t *hv);
void TDKillLine_finished(tap_dance_state_t *state, void *user_data);
void TDKillLine_reset(tap_dance_state_t *state, void *user_data);

bool _ctrl_g_new(keyrecord_t *record, uint16_t _);

bool IsShiftToggled(void);
