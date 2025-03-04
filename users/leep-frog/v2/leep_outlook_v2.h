// See here for outlook keyboard shortcuts:
// https://support.microsoft.com/en-us/office/keyboard-shortcuts-for-outlook-3cdeb221-7ae5-4c1d-8c1d-9e63216c1efd#PickTab=Windows

// Outlook aliases
#define OL_UP CL(COMMA)
#define OL_DOWN CL(DOT)
#define OL_READ C(KC_Q)
#define OL_UNRD C(KC_U)
#define OL_DEL KC_DEL
#define OL_PREV C(KC_COMMA)
#define OL_NEXT C(KC_DOT)
// This activates a custom command in classic Outlook. For Citadel, this is assigned to move to 'Read' folder
#define OL_MOVE C(S(KC_5))
#define OL_UNDO C(KC_Z)

// Outlook move left pane
#define OL_LEFT RCTL(SH(TAB))
// Outlook move right pane
#define OL_RGHT KC_F6

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
