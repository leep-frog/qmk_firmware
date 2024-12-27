
// Outlook aliases
#define OL_UP CL(COMMA)
#define OL_DOWN CL(DOT)
#define OL_READ C(KC_Q)
#define OL_UNRD C(KC_U)
#define OL_DEL KC_DEL
#define OL_PREV C(KC_COMMA)
#define OL_NEXT C(KC_DOT)
#define OL_MOVE C(S(KC_5)) // This activates a custom command in classic Outlook. For Citadel, this is assigned to move to 'Read' folder
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
