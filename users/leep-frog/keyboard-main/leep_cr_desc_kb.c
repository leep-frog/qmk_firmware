
const uint8_t cr_desc_line_moves[] = {
  // Deployability section
  91, 40, 40, 56,
  // Testing section
  51, 209, 123, 99, 79, 83,
  // Testing section
  69, 81, 97, 78,
  // End (move a one line below the last comment so we see the bottom
  // of the details input box).
  // Note: 53 is number of characters to next line, so (presumably) this number
  // brings us three lines below the last one
  53 + 2,
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
    // Go to first entry
    REPEAT_11(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_TAP(X_RIGHT)
  );
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

  for (int i = 0; i < cr_desc_line_moves[cr_desc_line_move_idx]; i++) {
    tap_code16(KC_RIGHT);
  }

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
