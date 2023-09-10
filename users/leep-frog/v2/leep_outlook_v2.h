
// Outlook aliases
#define OL_READ C(KC_Q)
#define OL_UNRD C(KC_U)
#define OL_DEL KC_DEL
#define OL_PREV C(KC_COMMA)
#define OL_NEXT C(KC_DOT)
// Outlook today is taken care of as custom keycode

/* TODO:
OL_REMOVE_FROM_CALENDAR
OL_ACCEPT_INVITE_DONT_SEND
OL_ACCEPT_INVITE_SEND
OL_CALENDAR_LEFT
OL_CALENDAR_RIGHT
*/

bool OutlookTodayHandler(keyrecord_t *record);
