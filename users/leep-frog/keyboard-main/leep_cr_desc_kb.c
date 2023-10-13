
const uint8_t cr_desc_line_moves[] = {
  // Deployability section
  1, 1, 1, 3,
  // Testing section
  1, 3, 2, 1, 1, 3,
  // Testing section
  1, 1, 1, 3,
  // End (move a few lines below the last comment so we see the bottom
  // of the details input box).
  3,
};

uint8_t cr_desc_line_move_idx = 0;
bool cr_desc_line_moving = false;

void StartCrDesc(void) {
  SEND_STRING(
    // Delete 'Revision N'
    REPEAT_7(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_RSFT(SS_TAP(X_END)) SS_TAP(X_BSPC)
    // Go to first entry
    REPEAT_11(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_TAP(X_RIGHT)
  );
  cr_desc_line_moving = true;
  cr_desc_line_move_idx = 0;
}

void EndCrDesc(void) {
  cr_desc_line_moving = false;
}

bool CrDescHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    StartCrDesc();
  }
  return false;
}

bool CrDescProcessHandler(uint16_t keycode, keyrecord_t* record) {
  if (!record->event.pressed) {
    // We want all key unpresses to proceed as normal
    return false;
  }

  if (!cr_desc_line_moving) {
    return false;
  }

  if (cr_desc_line_move_idx >= (sizeof(cr_desc_line_moves)/sizeof(cr_desc_line_moves[0]))) {
    return false;
  }

  switch (keycode) {
  case TD_A:
  case KC_SLSH:
  case TO_OTLK: // Semi-colon
    SEND_STRING("n/a");
    break;
  case KC_N:
    SEND_STRING("n");
    break;
  case TD_Y:
    SEND_STRING("y");
    break;
  case KC_S:
  case KC_K:
    // Just skip
    break;
  default:
    // End the mode, but don't process the key (like alt-mode breaking)
    EndCrDesc();
    return true;
  }

  for (int i = 0; i < cr_desc_line_moves[cr_desc_line_move_idx]; i++) {
    tap_code16(KC_DOWN);
  }
  tap_code16(KC_RIGHT);
  tap_code16(KC_RIGHT);

  cr_desc_line_move_idx++;

  return true;
}
