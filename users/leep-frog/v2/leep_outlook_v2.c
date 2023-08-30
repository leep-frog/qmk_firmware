
bool OutlookReloadHandler(bool pressed) {
  if (pressed) {
    // Switch panes
    send_string(SS_RCTL(SS_RSFT(SS_TAP(X_TAB))));
    // Reload
    tap_code16(KC_F5);
    // Swtich panes again
    send_string(SS_RCTL(SS_TAP(X_TAB)));
  }

  return true;
}

bool OutlookTodayHandler(keyrecord_t *record) {
  if (record->event.pressed) {
    SEND_STRING(
      // Switch panes
      SS_RCTL(SS_RSFT(SS_TAP(X_TAB)))
      SS_DELAY(100)
      // Reload
      SS_TAP(X_F5)
      SS_DELAY(100)
      // Swtich panes again
      SS_RCTL(SS_TAP(X_TAB))
    );
  }

  return true;
}
