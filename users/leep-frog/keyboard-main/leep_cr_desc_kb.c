// Number of ctrl+right keys to `Revision N` line
const uint8_t cr_desc_to_first = 37;

const uint8_t cr_desc_line_moves[] = {
  // Deployability section
  30, 8, 9, 13,
  // Testing section
  12, 111, 28, 17, 15, 18,
  // Testing section
  14, 15, 22, 15,
  // End (move a one line below the last comment so we see the bottom
  // of the details input box).
  // Note: 10 is number of word-right moves to next line, so (presumably) this number
  // brings us three lines below the last one
  12 + 2,
};

const uint16_t cr_desc_default_answers[] = {
  // Deployability section
  TD_Y, TD_Y, TD_Y, TD_Y,
  // Testing section
  TD_Y, TD_Y, TD_Y, KC_N, KC_N, KC_N,
  // Testing section
  KC_N, KC_N, KC_N, KC_N,
  // Git commit line
  TD_Y,
};

uint8_t cr_desc_line_move_idx = 0;
bool cr_desc_line_moving = false;

void StartCrDesc(void) {
  SEND_STRING(
    // Delete 'Revision N'
    REPEAT_7(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_RSFT(SS_TAP(X_END)) SS_TAP(X_BSPC)
  );

  // Move to first entry
  for (uint8_t i = 0; i < cr_desc_to_first; i++) {
    tap_code16(RCTL(KC_RIGHT));
  }
  tap_code16(KC_RIGHT); // Once for next line
  tap_code16(KC_RIGHT); // Once to center in bracket

  // Variable setup
  cr_desc_line_moving = true;
  cr_desc_line_move_idx = 0;
}

void EndCrDesc(void) {
  cr_desc_line_moving = false;
}

bool CrDescProcessHandler(uint16_t keycode, bool pressed) {
  if (!pressed) {
    // We want all key unpresses to proceed as normal
    return false;
  }

  if (!cr_desc_line_moving) {
    return false;
  }

  if (cr_desc_line_move_idx >= (sizeof(cr_desc_line_moves)/sizeof(cr_desc_line_moves[0]))) {
    EndCrDesc(); // In case it wasn't ended before
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

  for (uint8_t i = 0; i < cr_desc_line_moves[cr_desc_line_move_idx]; i++) {
    tap_code16(RCTL(KC_RIGHT));
  }
  tap_code16(KC_RIGHT); // Once for next line
  tap_code16(KC_RIGHT); // Once to center in bracket

  // Check if done
  if (++cr_desc_line_move_idx >= (sizeof(cr_desc_line_moves)/sizeof(cr_desc_line_moves[0]))) {
    EndCrDesc();
  }

  return true;
}

bool CrDefaultHandler() {
  StartCrDesc();
  for (uint8_t i = 0; i < sizeof(cr_desc_default_answers)/sizeof(cr_desc_default_answers[0]); i++) {
    CrDescProcessHandler(cr_desc_default_answers[i], true);
  }
  EndCrDesc();
  return false;
}
