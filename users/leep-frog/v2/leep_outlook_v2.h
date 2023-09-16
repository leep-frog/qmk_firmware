
// Outlook aliases
#define OL_READ C(KC_Q)
#define OL_UNRD C(KC_U)
#define OL_DEL KC_DEL
#define OL_PREV C(KC_COMMA)
#define OL_NEXT C(KC_DOT)
// Outlook today is taken care of as custom keycode

#define OL_TDAY_STRING() SS_RALT(SS_TAP(X_H)) SS_TAP(X_O) SS_TAP(X_D)

/* TODO:
OL_REMOVE_FROM_CALENDAR
OL_ACCEPT_INVITE_DONT_SEND
OL_ACCEPT_INVITE_SEND
OL_CALENDAR_LEFT
OL_CALENDAR_RIGHT
*/

bool OutlookReloadHandler(keyrecord_t* record, custom_keycode_value_t *_);
bool OutlookTodayHandler(keyrecord_t* record, custom_keycode_value_t *_);
