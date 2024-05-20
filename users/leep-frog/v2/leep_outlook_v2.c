
bool OutlookReloadHandler(keyrecord_t* record, custom_keycode_value_t *_) {
  if (record->event.pressed) {
    // Switch panes
    send_string(SS_RCTL(SS_RSFT(SS_TAP(X_TAB))));
    // Reload
    tap_code16(KC_F5);
    // Swtich panes again
    send_string(SS_RCTL(SS_TAP(X_TAB)));
  }

  return true;
}

bool OutlookTodayHandler(keyrecord_t* record, custom_keycode_value_t *_) {
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
