#pragma once

#include "./leep_enum_kb.h"
#include "../v2/leep_outlook_v2.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
// Can't just extern (https://stackoverflow.com/questions/14069737/switch-case-error-case-label-does-not-reduce-to-an-integer-constant)
bool IsToggleShiftTapDance(uint16_t keycode);

#define TGL_SHF TD(TDK_SHIFT_TOGGLE)

#define CK_KILL TD(TDK_KILL_LINE)
#define CK_MCR1 TD(TDK_MACRO_1)
#define CK_MCR2 TD(TDK_MACRO_2)
#define CK_DEL_WORD RCTL(KC_DELETE)
#define CK_MDPS TD(TDK_MARKDOWN_PASTE)
// Outlook reload
#define OL_RLD TD(TDK_OUTLOOK_RELOAD)
#define OL_RGHT KC_F6
#define TD_A TD(TDK_A)
#define TD_B TD(TDK_B)
#define TD_C TD(TDK_C)
#define TD_I TD(TDK_I)
#define TD_S TD(TDK_S)
#define TD_U TD(TDK_U)
#define TD_V TD(TDK_V)
#define TD_Y TD(TDK_Y)
#define OH_COPY TD(TDK_OH_COPY)
#define OH_PSTE TD(TDK_OH_PASTE)
#define TO_SCRL TD(TDK_SCROLL_LEFT)
#define TO_SCRR TD(TDK_SCROLL_RIGHT)

#define TO_SYMB TD(TDK_SYMB_LAYER)
#define TD_TBSF TD(TDK_TAB_SHIFT)

#define TO_OTLK TD(TDK_TO_OUTLOOK)
#define TO_SHCT TD(TDK_TO_SHORTCUT)
#define TO_NAV TD(TDK_TO_NAV)
#define TO_NAVB TD(TDK_TO_NAV_RCBR)

#define TO_BASE_FROM_ELLA TD(TDK_ELLA_MODE)

#define TD_CRDC TD(TDK_CR_DESC)
