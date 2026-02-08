#pragma once

#include "users/leep-frog/v2/leep_custom_keycodes_v2.h"
#include "users/leep-frog/keyboard-main/leep_symbol_layer_overlap_kb.h"

// Note: we don't need to organize by handler type,
// but do so for readability.
// TODO: Change CK prefix to CKE (CK Enum) since these are actually starting at 0 and not SAFE_RANGE (see CK(...)s below for proper values)
enum custom_keycode_handlers {
  // Fn handlers
  TO_CTLX_HANDLER,
  CTRL_W_HANDLER,
  CK_WAIT_HANDLER,
  CK_ATB_HANDLER,
  CK_SATB_HANDLER,
  CK_ACL_HANDLER,
  CK_LOCK_HANDLER,
  CK_RESET_HANDLER,
  KB_OFF_HANDLER,
  CK_EYE_HANDLER,
  SLACK_EDIT_HANDLER,
  MS_CTRL_HANDLER,
  CK_ALTT_HANDLER,
  CK_MUTS_HANDLER,
  CK_MUT_HANDLER,
  CK_CTLG_HANDLER,
  CK_TGL_SHIFT_HANDLER,
  // String handlers
  CK_UNBS_HANDLER,
  CK_LOGS_HANDLER,
  URL_PST_HANDLER,
  URL_CPY_HANDLER,
  OL_TDAY_HANDLER,
  CK_VERSION_HANDLER,
  CK_DOWNLOAD_GCS,
  CK_OSM_SHIFT_HANDLER,
  CK_USER_HANDLER,
  CK_EMAIL_HANDLER,

#ifdef LEEP_TEST_MODE
  // CK_TEST_CONFIRM is used by tests to confirm that the keyboard
  // is back in a default state
  CK_TEST_CONFIRM,
#endif
};

#define TO_CTLX CK(TO_CTLX_HANDLER)
#define CTRL_W CK(CTRL_W_HANDLER)
#define CK_WAIT CK(CK_WAIT_HANDLER)
#define CK_ATB CK(CK_ATB_HANDLER)
#define CK_SATB CK(CK_SATB_HANDLER)
#define CK_ACL CK(CK_ACL_HANDLER)
#define CK_LOCK CK(CK_LOCK_HANDLER)
#define CK_RST CK(CK_RESET_HANDLER)
#define KB_OFF CK(KB_OFF_HANDLER)
#define CK_EYE CK(CK_EYE_HANDLER)
#define SK_EDIT CK(SLACK_EDIT_HANDLER)
#define MS_CTRL CK(MS_CTRL_HANDLER)
#define CK_ALTT CK(CK_ALTT_HANDLER)
#define CK_MUTS CK(CK_MUTS_HANDLER)
#define CK_MUT CK(CK_MUT_HANDLER)
#define CK_CTLG CK(CK_CTLG_HANDLER)
#define CK_TGSH CK(CK_TGL_SHIFT_HANDLER)

#define URL_PST CK(URL_PST_HANDLER)
#define URL_CPY CK(URL_CPY_HANDLER)
#define OL_TDAY CK(OL_TDAY_HANDLER)
#define CK_UNBS CK(CK_UNBS_HANDLER)
#define CK_LOGS CK(CK_LOGS_HANDLER)
#define CK_VRSN CK(CK_VERSION_HANDLER)
#define CK_GCS CK(CK_DOWNLOAD_GCS)
#define CK_SHFT CK(CK_OSM_SHIFT_HANDLER)
#define CK_USER CK(CK_USER_HANDLER)
#define CK_EMAIL CK(CK_EMAIL_HANDLER)

#ifdef LEEP_TEST_MODE
extern char test_message[];
#define CK_TEST CK(CK_TEST_CONFIRM)
#endif

bool leep_process_record_user(uint16_t keycode, keyrecord_t* record);

/***********
* Keycodes *
************/

// LR_ELLA layer
// Number row
#define LK_ELLA_ESC KC_ESC
#define LK_ELLA_1 KC_1
#define LK_ELLA_2 KC_2
#define LK_ELLA_3 KC_3
#define LK_ELLA_4 KC_4
#define LK_ELLA_5 KC_5
#define LK_ELLA_6 KC_6
#define LK_ELLA_7 KC_7
#define LK_ELLA_8 KC_8
#define LK_ELLA_9 KC_9
#define LK_ELLA_0 KC_0
#define LK_ELLA_MINUS KC_MINUS
#define LK_ELLA_EQUAL KC_EQUAL
// Top row
#define LK_ELLA_TAB KC_TAB
#define LK_ELLA_Q KC_Q
#define LK_ELLA_W KC_W
#define LK_ELLA_E KC_E
#define LK_ELLA_R KC_R
#define LK_ELLA_T KC_T
#define LK_ELLA_Y KC_Y
#define LK_ELLA_U KC_U
#define LK_ELLA_I KC_I
#define LK_ELLA_O KC_O
#define LK_ELLA_P KC_P
#define LK_ELLA_LBRC KC_LBRC
#define LK_ELLA_RBRC KC_RBRC
// Middle row
#define LK_ELLA_CAPS_LOCK KC_LSFT
#define LK_ELLA_A KC_A
#define LK_ELLA_S KC_S
#define LK_ELLA_D KC_D
#define LK_ELLA_F KC_F
#define LK_ELLA_G KC_G
#define LK_ELLA_H KC_H
#define LK_ELLA_J KC_J
#define LK_ELLA_K KC_K
#define LK_ELLA_L KC_L
#define LK_ELLA_SC KC_SCLN
#define LK_ELLA_QUOTE KC_QUOTE
#define LK_ELLA_ENTER KC_ENTER
// Bottom row
#define LK_ELLA_LSFT KC_LSFT
#define LK_ELLA_Z KC_Z
#define LK_ELLA_X KC_X
#define LK_ELLA_C KC_C
#define LK_ELLA_V KC_V
#define LK_ELLA_B KC_B
#define LK_ELLA_N KC_N
#define LK_ELLA_M KC_M
#define LK_ELLA_LT KC_COMM
#define LK_ELLA_GT KC_DOT
#define LK_ELLA_SL KC_SLSH
#define LK_ELLA_RSFT KC_RSFT
// Thumbs
// Recently switched these to TO_XYZ_KEYCODE. If noticing any
// issues with OSM (being stuck in LR_ELLA), it may be due to these changes.
#define LK_ELLA_LEFT_THUMB_PRIMARY KC_RSFT
#define LK_ELLA_LEFT_THUMB_SECONDARY TO_ALT_KEYCODE
#define LK_ELLA_LEFT_THUMB_TERTIARY KC_LGUI
#define LK_ELLA_RIGHT_THUMB_PRIMARY TO_SYMB_KEYCODE
#define LK_ELLA_RIGHT_THUMB_SECONDARY TO_CTRL_KEYCODE
#define LK_ELLA_RIGHT_THUMB_TERTIARY KC_RGUI


// LR_BASE layer
// Number row
#define LK_BASE_ESC KC_ESC
#define LK_BASE_1 KC_1
#define LK_BASE_2 KC_2
#define LK_BASE_3 KC_3
#define LK_BASE_4 KC_4
#define LK_BASE_5 KC_5
#define LK_BASE_6 KC_6
#define LK_BASE_7 KC_7
#define LK_BASE_8 KC_8
#define LK_BASE_9 KC_9
#define LK_BASE_0 KC_0
#define LK_BASE_MINUS KC_MINUS
#define LK_BASE_EQUAL KC_EQUAL
// Top row
#define LK_BASE_TAB KC_TAB
#define LK_BASE_Q KC_Q
#define LK_BASE_W KC_W
#define LK_BASE_E KC_E
#define LK_BASE_R KC_R
#define LK_BASE_T KC_T
#define LK_BASE_Y TD_Y
#define LK_BASE_U TD_U
#define LK_BASE_I TD_I
#define LK_BASE_O KC_O
#define LK_BASE_P KC_P
#define LK_BASE_LBRC KC_LBRC
#define LK_BASE_RBRC KC_RBRC
// Middle row
#define LK_BASE_CAPS_LOCK SC_LSPO
#define LK_BASE_A KC_A
#define LK_BASE_S TD_S
#define LK_BASE_D KC_D
#define LK_BASE_F KC_F
#define LK_BASE_G KC_G
#define LK_BASE_H KC_H
#define LK_BASE_J KC_J
#define LK_BASE_K KC_K
#define LK_BASE_L KC_L
#define LK_BASE_SC TO_OTLK
#define LK_BASE_QUOTE SC_RSPC
#define LK_BASE_ENTER KC_ENTER
// Bottom row
#define LK_BASE_LSFT TD_LCBR
#define LK_BASE_Z KC_Z
#define LK_BASE_X KC_X
#define LK_BASE_C TD_C
#define LK_BASE_V TD_V
#define LK_BASE_B TD_B
#define LK_BASE_N KC_N
#define LK_BASE_M KC_M
#define LK_BASE_LT KC_COMM
#define LK_BASE_GT KC_DOT
#define LK_BASE_SL KC_SLSH
#define LK_BASE_RSFT TD_RCBR
// Thumbs
#define LK_BASE_LEFT_THUMB_PRIMARY CK_SHFT
#define LK_BASE_LEFT_THUMB_SECONDARY TO_ALT
#define LK_BASE_LEFT_THUMB_TERTIARY TO_SHCT
#define LK_BASE_RIGHT_THUMB_PRIMARY TO_SYMB
#define LK_BASE_RIGHT_THUMB_SECONDARY TO_CTRL
#define LK_BASE_RIGHT_THUMB_TERTIARY TO_SHCT

// LR_CTRL layer
// Number row
#define LK_CTRL_ESC CL(ESC)
#define LK_CTRL_1 CL(1)
#define LK_CTRL_2 CL(2)
#define LK_CTRL_3 CL(3)
#define LK_CTRL_4 CL(4)
#define LK_CTRL_5 CL(5)
#define LK_CTRL_6 CL(6)
#define LK_CTRL_7 CL(7)
#define LK_CTRL_8 CL(8)
#define LK_CTRL_9 CL(9)
#define LK_CTRL_0 CL(0)
#define LK_CTRL_MINUS CL(MINUS)
#define LK_CTRL_EQUAL CL(EQUAL)
// Top row
#define LK_CTRL_TAB CL(TAB)
#define LK_CTRL_Q CL(Q)
#define LK_CTRL_W CTRL_W
#define LK_CTRL_E KC_END
#define LK_CTRL_R CL(R)
#define LK_CTRL_T CL(T)
#define LK_CTRL_Y CL(Y)
#define LK_CTRL_U CK_TABB
#define LK_CTRL_I CL(I)
#define LK_CTRL_O CK_TABF
#define LK_CTRL_P KC_UP
#define LK_CTRL_LBRC CL(LBRC)
#define LK_CTRL_RBRC CL(RBRC)
// Middle row
// TODO: Make this ctrl_shift layer
#define LK_CTRL_CAPS_LOCK KC_LSFT
#define LK_CTRL_A KC_HOME
#define LK_CTRL_S CL(F)
#define LK_CTRL_D KC_DEL
#define LK_CTRL_F KC_RGHT
#define LK_CTRL_G CK_CTLG
#define LK_CTRL_H KC_BSPC
#define LK_CTRL_J TGL_SHF
#define LK_CTRL_K CK_KILL
#define LK_CTRL_L KC_PGUP
#define LK_CTRL_SC TO_CTSH
#define LK_CTRL_QUOTE TD(TDK_CTRL_SHIFT_TOGGLE)
#define LK_CTRL_ENTER CL(ENT)
// Bottom row
#define LK_CTRL_LSFT CL(LSFT)
#define LK_CTRL_Z CL(Z)
#define LK_CTRL_X TO_CTLX
#define LK_CTRL_C CK_COPY
#define LK_CTRL_V KC_PGDN
#define LK_CTRL_B KC_LEFT
#define LK_CTRL_N KC_DOWN
#define LK_CTRL_M CL(M)
#define LK_CTRL_LT CL(COMM)
#define LK_CTRL_GT CL(DOT)
#define LK_CTRL_SL CL(SLSH)
#define LK_CTRL_RSFT CL(RSFT)
// Thumbs
#define LK_CTRL_LEFT_THUMB_PRIMARY CL(ENTER)
#define LK_CTRL_LEFT_THUMB_SECONDARY MO(LR_CTRL_SHIFT)
#define LK_CTRL_LEFT_THUMB_TERTIARY CL(LGUI)
#define LK_CTRL_RIGHT_THUMB_PRIMARY CL(SPACE)
#define LK_CTRL_RIGHT_THUMB_SECONDARY _______
#define LK_CTRL_RIGHT_THUMB_TERTIARY CL(RGUI)


// LR_CTRL_SHIFT layer
// Number row
#define LK_CTRL_SHIFT_ESC _______
#define LK_CTRL_SHIFT_1 _______
#define LK_CTRL_SHIFT_2 _______
#define LK_CTRL_SHIFT_3 _______
#define LK_CTRL_SHIFT_4 _______
#define LK_CTRL_SHIFT_5 _______
#define LK_CTRL_SHIFT_6 _______
#define LK_CTRL_SHIFT_7 _______
#define LK_CTRL_SHIFT_8 _______
#define LK_CTRL_SHIFT_9 _______
#define LK_CTRL_SHIFT_0 _______
#define LK_CTRL_SHIFT_MINUS _______
#define LK_CTRL_SHIFT_EQUAL _______
// Top row
#define LK_CTRL_SHIFT_TAB _______
#define LK_CTRL_SHIFT_Q AL(Q)
#define LK_CTRL_SHIFT_W AL(F4)
#define LK_CTRL_SHIFT_E _______
#define LK_CTRL_SHIFT_R _______
#define LK_CTRL_SHIFT_T CK_ALTT
#define LK_CTRL_SHIFT_Y CK_PSTE
#define LK_CTRL_SHIFT_U CK_STBB
#define LK_CTRL_SHIFT_I CL_SH(I)
#define LK_CTRL_SHIFT_O CK_STBF
#define LK_CTRL_SHIFT_P KC_PGUP
#define LK_CTRL_SHIFT_LBRC _______
#define LK_CTRL_SHIFT_RBRC _______
// Middle row
#define LK_CTRL_SHIFT_CAPS_LOCK _______
#define LK_CTRL_SHIFT_A TD_A
#define LK_CTRL_SHIFT_S CL_SH(F)
#define LK_CTRL_SHIFT_D CL(DEL)
#define LK_CTRL_SHIFT_F CL(RGHT)
#define LK_CTRL_SHIFT_G _______
#define LK_CTRL_SHIFT_H CK_UNBS
#define LK_CTRL_SHIFT_J CK_TGSH
#define LK_CTRL_SHIFT_K _______
#define LK_CTRL_SHIFT_L SH(PGUP)
#define LK_CTRL_SHIFT_SC _______
#define LK_CTRL_SHIFT_QUOTE _______
#define LK_CTRL_SHIFT_ENTER _______
// Bottom row
#define LK_CTRL_SHIFT_LSFT _______
#define LK_CTRL_SHIFT_Z AL(Z)
#define LK_CTRL_SHIFT_X _______
#define LK_CTRL_SHIFT_C _______
#define LK_CTRL_SHIFT_V SH(PGDN)
#define LK_CTRL_SHIFT_B CL(LEFT)
#define LK_CTRL_SHIFT_N KC_PGDN
#define LK_CTRL_SHIFT_M _______
#define LK_CTRL_SHIFT_LT _______
#define LK_CTRL_SHIFT_GT _______
#define LK_CTRL_SHIFT_SL _______
#define LK_CTRL_SHIFT_RSFT _______
// Thumbs
#define LK_CTRL_SHIFT_LEFT_THUMB_PRIMARY _______
#define LK_CTRL_SHIFT_LEFT_THUMB_SECONDARY _______
#define LK_CTRL_SHIFT_LEFT_THUMB_TERTIARY _______
#define LK_CTRL_SHIFT_RIGHT_THUMB_PRIMARY _______
#define LK_CTRL_SHIFT_RIGHT_THUMB_SECONDARY _______
#define LK_CTRL_SHIFT_RIGHT_THUMB_TERTIARY _______

// LR_CTRL_X layer
// Number row
#define LK_CTRL_X_ESC CL(ESC)
#define LK_CTRL_X_1 CL(1)
#define LK_CTRL_X_2 CL(2)
#define LK_CTRL_X_3 CL(3)
#define LK_CTRL_X_4 CL(4)
#define LK_CTRL_X_5 CL(5)
#define LK_CTRL_X_6 CL(6)
#define LK_CTRL_X_7 CL(7)
#define LK_CTRL_X_8 CL(8)
#define LK_CTRL_X_9 CL(9)
#define LK_CTRL_X_0 CL(0)
#define LK_CTRL_X_MINUS CL(MINUS)
#define LK_CTRL_X_EQUAL CL(EQUAL)
// Top row
#define LK_CTRL_X_TAB CL(TAB)
#define LK_CTRL_X_Q CL(Q)
#define LK_CTRL_X_W CL(W)
#define LK_CTRL_X_E CL(E)
#define LK_CTRL_X_R CL(R)
#define LK_CTRL_X_T CL(T)
#define LK_CTRL_X_Y CL(Y)
#define LK_CTRL_X_U CL(U)
#define LK_CTRL_X_I CL(I)
#define LK_CTRL_X_O CL(O)
#define LK_CTRL_X_P CL(P)
#define LK_CTRL_X_LBRC CL(LBRC)
#define LK_CTRL_X_RBRC CL(RBRC)
// Middle row
#define LK_CTRL_X_CAPS_LOCK CL(LSFT)
#define LK_CTRL_X_A CL(A)
#define LK_CTRL_X_S CL(S)
#define LK_CTRL_X_D CL(D)
#define LK_CTRL_X_F CL(F)
#define LK_CTRL_X_G CL(G)
#define LK_CTRL_X_H CL(H)
#define LK_CTRL_X_J CL(J)
#define LK_CTRL_X_K CL(K)
#define LK_CTRL_X_L CL(L)
#define LK_CTRL_X_SC CL(SCLN)
#define LK_CTRL_X_QUOTE CL(QUOT)
#define LK_CTRL_X_ENTER CL(ENTER)
// Bottom row
#define LK_CTRL_X_LSFT CL(LSFT)
#define LK_CTRL_X_Z CL(Z)
#define LK_CTRL_X_X CL(X)
#define LK_CTRL_X_C CL(C)
#define LK_CTRL_X_V CL(V)
#define LK_CTRL_X_B CL(B)
#define LK_CTRL_X_N CL(N)
#define LK_CTRL_X_M CL(M)
#define LK_CTRL_X_LT CL(COMM)
#define LK_CTRL_X_GT CL(DOT)
#define LK_CTRL_X_SL CL(SLSH)
#define LK_CTRL_X_RSFT CL(RSFT)
// Thumbs
#define LK_CTRL_X_LEFT_THUMB_PRIMARY CL(ENTER)
#define LK_CTRL_X_LEFT_THUMB_SECONDARY CL(TAB)
#define LK_CTRL_X_LEFT_THUMB_TERTIARY CL(LGUI)
#define LK_CTRL_X_RIGHT_THUMB_PRIMARY CL(SPACE)
#define LK_CTRL_X_RIGHT_THUMB_SECONDARY _______
#define LK_CTRL_X_RIGHT_THUMB_TERTIARY CL(RGUI)



// LR_ALT layer
// Number row
#define LK_ALT_ESC AL(ESC)
#define LK_ALT_1 AL(1)
#define LK_ALT_2 AL(2)
#define LK_ALT_3 AL(3)
#define LK_ALT_4 AL(4)
#define LK_ALT_5 AL(5)
#define LK_ALT_6 AL(6)
#define LK_ALT_7 AL(7)
#define LK_ALT_8 AL(8)
#define LK_ALT_9 AL(9)
#define LK_ALT_0 AL(0)
#define LK_ALT_MINUS AL(MINUS)
#define LK_ALT_EQUAL AL(EQUAL)
// Top row
#define LK_ALT_TAB AL(TAB)
#define LK_ALT_Q AL(Q)
#define LK_ALT_W AL(F4)
#define LK_ALT_E AL(E)
#define LK_ALT_R AL(R)
#define LK_ALT_T CK_ALTT
#define LK_ALT_Y CK_PSTE
#define LK_ALT_U CK_SATB
#define LK_ALT_I AL(I)
#define LK_ALT_O CK_ATB
#define LK_ALT_P AL(P)
#define LK_ALT_LBRC AL(LBRC)
#define LK_ALT_RBRC AL(RBRC)
// Middle row
#define LK_ALT_CAPS_LOCK KC_LSFT
#define LK_ALT_A TD_A
#define LK_ALT_S AL(S)
#define LK_ALT_D CL(DEL)
#define LK_ALT_F CL(RGHT)
#define LK_ALT_G AL(G)
#define LK_ALT_H CK_UNBS
#define LK_ALT_J CK_TGSH
#define LK_ALT_K AL(K)
#define LK_ALT_L AL(L)
#define LK_ALT_SC AL(SCLN)
#define LK_ALT_QUOTE KC_RSFT
#define LK_ALT_ENTER CL(ENTER)
// Bottom row
#define LK_ALT_LSFT AL(LSFT)
#define LK_ALT_Z AL(Z)
#define LK_ALT_X AL(X)
#define LK_ALT_C AL(C)
#define LK_ALT_V AL(V)
#define LK_ALT_B CL(LEFT)
#define LK_ALT_N AL(N)
#define LK_ALT_M AL(M)
#define LK_ALT_LT AL(COMM)
#define LK_ALT_GT AL(DOT)
#define LK_ALT_SL AL(SLSH)
#define LK_ALT_RSFT AL(RSFT)
// Thumbs
#define LK_ALT_LEFT_THUMB_PRIMARY AL(ENTER)
#define LK_ALT_LEFT_THUMB_SECONDARY _______
#define LK_ALT_LEFT_THUMB_TERTIARY AL(LGUI)
#define LK_ALT_RIGHT_THUMB_PRIMARY _______
#define LK_ALT_RIGHT_THUMB_SECONDARY AL(ENTER)
#define LK_ALT_RIGHT_THUMB_TERTIARY AL(RGUI)

// LR_SYMB layer
// Number row
#define LK_SYMB_ESC KC_ESC
#define LK_SYMB_1 KC_F1
#define LK_SYMB_2 KC_F2
#define LK_SYMB_3 KC_F3
#define LK_SYMB_4 KC_F4
#define LK_SYMB_5 KC_F5
#define LK_SYMB_6 KC_F6
#define LK_SYMB_7 KC_F7
#define LK_SYMB_8 KC_F8
#define LK_SYMB_9 KC_F9
#define LK_SYMB_0 KC_F10
#define LK_SYMB_MINUS KC_F11
#define LK_SYMB_EQUAL KC_F22
// Top row
#define LK_SYMB_TAB KC_TAB
#define LK_SYMB_Q KC_EXLM
#define LK_SYMB_W KC_AT
#define LK_SYMB_E KC_HASH
#define LK_SYMB_R KC_DOLLAR
#define LK_SYMB_T KC_PERC
#define LK_SYMB_Y KC_CIRC
#define LK_SYMB_U KC_AMPR
#define LK_SYMB_I KC_ASTR
#define LK_SYMB_O KC_MINUS
#define LK_SYMB_P KC_PLUS
#define LK_SYMB_LBRC KC_LBRC
#define LK_SYMB_RBRC KC_RBRC
// Middle row
#define LK_SYMB_CAPS_LOCK KC_LPRN
#define LK_SYMB_A KC_1
#define LK_SYMB_S KC_2
#define LK_SYMB_D KC_3
#define LK_SYMB_F KC_4
#define LK_SYMB_G KC_5
#define LK_SYMB_H KC_6
#define LK_SYMB_J KC_7
#define LK_SYMB_K KC_8
#define LK_SYMB_L KC_9
#define LK_SYMB_SC KC_0
#define LK_SYMB_QUOTE KC_RPRN  // TODO: shift on hold? was causing issues before. Same for LK_SYMB_CAPS_LOCK
#define LK_SYMB_ENTER KC_ENTER
// Bottom row
#define LK_SYMB_LSFT KC_LCBR
#define LK_SYMB_Z KC_EQUAL
#define LK_SYMB_X KC_UNDERSCORE
#define LK_SYMB_C KC_LBRC
#define LK_SYMB_V CK_MDPS
#define LK_SYMB_B KC_BSLS
#define LK_SYMB_N KC_N
#define LK_SYMB_M KC_PIPE
#define LK_SYMB_LT KC_COMM
#define LK_SYMB_GT KC_DOT
#define LK_SYMB_SL KC_SLSH
#define LK_SYMB_RSFT KC_RCBR
// Thumbs
#define LK_SYMB_LEFT_THUMB_PRIMARY KC_SPACE
#define LK_SYMB_LEFT_THUMB_SECONDARY KC_ENTER
#define LK_SYMB_LEFT_THUMB_TERTIARY _______
#define LK_SYMB_RIGHT_THUMB_PRIMARY _______
#define LK_SYMB_RIGHT_THUMB_SECONDARY KC_ENTER
#define LK_SYMB_RIGHT_THUMB_TERTIARY KC_RGUI

// LR_SHORTCUTS layer
// This layer used to have GD_HD_1/2/3/..., but removed after refactor. Re-add in this section if needed
// Number row
#define LK_SHORTCUTS_ESC _______
#define LK_SHORTCUTS_1 _______
#define LK_SHORTCUTS_2 _______
#define LK_SHORTCUTS_3 _______
#define LK_SHORTCUTS_4 _______
#define LK_SHORTCUTS_5 _______
#define LK_SHORTCUTS_6 _______
#define LK_SHORTCUTS_7 _______
#define LK_SHORTCUTS_8 _______
#define LK_SHORTCUTS_9 _______
#define LK_SHORTCUTS_0 _______
#define LK_SHORTCUTS_MINUS _______
#define LK_SHORTCUTS_EQUAL _______
// Top row
#define LK_SHORTCUTS_TAB _______
#define LK_SHORTCUTS_Q AL(Q)
#define LK_SHORTCUTS_W AL(F4)
#define LK_SHORTCUTS_E SK_EDIT
#define LK_SHORTCUTS_R CK_RST
#define LK_SHORTCUTS_T _______
#define LK_SHORTCUTS_Y _______
#define LK_SHORTCUTS_U CK_USER
#define LK_SHORTCUTS_I _______
#define LK_SHORTCUTS_O _______
#define LK_SHORTCUTS_P GU(UP)
#define LK_SHORTCUTS_LBRC _______
#define LK_SHORTCUTS_RBRC _______
// Middle row
#define LK_SHORTCUTS_CAPS_LOCK _______
#define LK_SHORTCUTS_A _______
#define LK_SHORTCUTS_S KC_BSPC
#define LK_SHORTCUTS_D KC_DEL
#define LK_SHORTCUTS_F GU(RIGHT)
#define LK_SHORTCUTS_G _______
#define LK_SHORTCUTS_H _______
#define LK_SHORTCUTS_J _______
#define LK_SHORTCUTS_K _______
#define LK_SHORTCUTS_L _______
#define LK_SHORTCUTS_SC _______
#define LK_SHORTCUTS_QUOTE _______
#define LK_SHORTCUTS_ENTER _______
// Bottom row
#define LK_SHORTCUTS_LSFT _______
#define LK_SHORTCUTS_Z _______
#define LK_SHORTCUTS_X _______
#define LK_SHORTCUTS_C CK_EMAIL
#define LK_SHORTCUTS_V CK_GCS
#define LK_SHORTCUTS_B GU(LEFT)
#define LK_SHORTCUTS_N GU(DOWN)
#define LK_SHORTCUTS_M _______
#define LK_SHORTCUTS_LT _______
#define LK_SHORTCUTS_GT _______
#define LK_SHORTCUTS_SL _______
#define LK_SHORTCUTS_RSFT _______
// Thumbs
#define LK_SHORTCUTS_LEFT_THUMB_PRIMARY _______
#define LK_SHORTCUTS_LEFT_THUMB_SECONDARY GU(TAB)
#define LK_SHORTCUTS_LEFT_THUMB_TERTIARY _______
#define LK_SHORTCUTS_RIGHT_THUMB_PRIMARY _______
#define LK_SHORTCUTS_RIGHT_THUMB_SECONDARY _______
#define LK_SHORTCUTS_RIGHT_THUMB_TERTIARY _______

// LR_OUTLOOK layer
// Number row
#define LK_OUTLOOK_ESC _______
#define LK_OUTLOOK_1 _______
#define LK_OUTLOOK_2 _______
#define LK_OUTLOOK_3 _______
#define LK_OUTLOOK_4 _______
#define LK_OUTLOOK_5 _______
#define LK_OUTLOOK_6 _______
#define LK_OUTLOOK_7 _______
#define LK_OUTLOOK_8 _______
#define LK_OUTLOOK_9 _______
#define LK_OUTLOOK_0 _______
#define LK_OUTLOOK_MINUS _______
#define LK_OUTLOOK_EQUAL _______
// Top row
#define LK_OUTLOOK_TAB _______
#define LK_OUTLOOK_Q _______
#define LK_OUTLOOK_W _______
#define LK_OUTLOOK_E _______
#define LK_OUTLOOK_R _______
#define LK_OUTLOOK_T _______
#define LK_OUTLOOK_Y CL(U)
#define LK_OUTLOOK_U CL(Q)
#define LK_OUTLOOK_I CL(COMMA)
#define LK_OUTLOOK_O CL(U)
#define LK_OUTLOOK_P _______
#define LK_OUTLOOK_LBRC _______
#define LK_OUTLOOK_RBRC _______
// Middle row
#define LK_OUTLOOK_CAPS_LOCK _______
#define LK_OUTLOOK_A _______
#define LK_OUTLOOK_S _______
#define LK_OUTLOOK_D _______
#define LK_OUTLOOK_F _______
#define LK_OUTLOOK_G _______
#define LK_OUTLOOK_H KC_DEL
#define LK_OUTLOOK_J OL_MOVE
#define LK_OUTLOOK_K CL(DOT)
#define LK_OUTLOOK_L OL_RLD
#define LK_OUTLOOK_SC _______
#define LK_OUTLOOK_QUOTE _______
#define LK_OUTLOOK_ENTER _______
// Bottom row
#define LK_OUTLOOK_LSFT _______
#define LK_OUTLOOK_Z _______
#define LK_OUTLOOK_X _______
#define LK_OUTLOOK_C _______
#define LK_OUTLOOK_V _______
#define LK_OUTLOOK_B _______
#define LK_OUTLOOK_N _______
#define LK_OUTLOOK_M OL_TDAY
#define LK_OUTLOOK_LT CL(U)
#define LK_OUTLOOK_GT _______
#define LK_OUTLOOK_SL CL(M)
#define LK_OUTLOOK_RSFT _______
// Thumbs
#define LK_OUTLOOK_LEFT_THUMB_PRIMARY _______
#define LK_OUTLOOK_LEFT_THUMB_SECONDARY _______
#define LK_OUTLOOK_LEFT_THUMB_TERTIARY _______
#define LK_OUTLOOK_RIGHT_THUMB_PRIMARY OL_RGHT
#define LK_OUTLOOK_RIGHT_THUMB_SECONDARY OL_LEFT
#define LK_OUTLOOK_RIGHT_THUMB_TERTIARY _______

// LR_ONE_HAND layer
// Number row
#define LK_ONE_HAND_ESC _______
#define LK_ONE_HAND_1 _______
#define LK_ONE_HAND_2 _______
#define LK_ONE_HAND_3 _______
#define LK_ONE_HAND_4 _______
#define LK_ONE_HAND_5 _______
#define LK_ONE_HAND_6 _______
#define LK_ONE_HAND_7 _______
#define LK_ONE_HAND_8 _______
#define LK_ONE_HAND_9 _______
#define LK_ONE_HAND_0 _______
#define LK_ONE_HAND_MINUS _______
#define LK_ONE_HAND_EQUAL _______
// Top row
#define LK_ONE_HAND_TAB _______
#define LK_ONE_HAND_Q _______
#define LK_ONE_HAND_W CL(W)
#define LK_ONE_HAND_E CK_SATB
#define LK_ONE_HAND_R CK_ATB
#define LK_ONE_HAND_T CL(T)
#define LK_ONE_HAND_Y CL(W)
#define LK_ONE_HAND_U CK_SATB
#define LK_ONE_HAND_I CK_ATB
#define LK_ONE_HAND_O CL(T)
#define LK_ONE_HAND_P _______
#define LK_ONE_HAND_LBRC _______
#define LK_ONE_HAND_RBRC _______
// Middle row
#define LK_ONE_HAND_CAPS_LOCK KC_LSFT
#define LK_ONE_HAND_A TO_SCRL
#define LK_ONE_HAND_S CL(R)
#define LK_ONE_HAND_D CK_TABB
#define LK_ONE_HAND_F CK_TABF
#define LK_ONE_HAND_G WS_RGHT
#define LK_ONE_HAND_H WS_LEFT
#define LK_ONE_HAND_J CK_TABB
#define LK_ONE_HAND_K CK_TABF
#define LK_ONE_HAND_L CL(R)
#define LK_ONE_HAND_SC TO_SCRR
#define LK_ONE_HAND_QUOTE KC_RSFT
#define LK_ONE_HAND_ENTER _______
// Bottom row
#define LK_ONE_HAND_LSFT _______
#define LK_ONE_HAND_Z CK_WWWB
#define LK_ONE_HAND_X CK_WWWF
#define LK_ONE_HAND_C OH_COPY
#define LK_ONE_HAND_V OH_PSTE
#define LK_ONE_HAND_B _______
#define LK_ONE_HAND_N OH_COPY
#define LK_ONE_HAND_M OH_PSTE
#define LK_ONE_HAND_LT CK_WWWB
#define LK_ONE_HAND_GT CK_WWWF
#define LK_ONE_HAND_SL _______
#define LK_ONE_HAND_RSFT _______
// Thumbs
#define LK_ONE_HAND_LEFT_THUMB_PRIMARY _______
#define LK_ONE_HAND_LEFT_THUMB_SECONDARY _______
#define LK_ONE_HAND_LEFT_THUMB_TERTIARY _______
#define LK_ONE_HAND_RIGHT_THUMB_PRIMARY _______
#define LK_ONE_HAND_RIGHT_THUMB_SECONDARY _______
#define LK_ONE_HAND_RIGHT_THUMB_TERTIARY _______

// LR_SCROLL layer
// Number row
#define LK_SCROLL_ESC _______
#define LK_SCROLL_1 _______
#define LK_SCROLL_2 _______
#define LK_SCROLL_3 _______
#define LK_SCROLL_4 _______
#define LK_SCROLL_5 _______
#define LK_SCROLL_6 _______
#define LK_SCROLL_7 _______
#define LK_SCROLL_8 _______
#define LK_SCROLL_9 _______
#define LK_SCROLL_0 _______
#define LK_SCROLL_MINUS _______
#define LK_SCROLL_EQUAL _______
// Top row
#define LK_SCROLL_TAB _______
#define LK_SCROLL_Q _______
#define LK_SCROLL_W _______
#define LK_SCROLL_E KC_WH_U
#define LK_SCROLL_R _______
#define LK_SCROLL_T _______
#define LK_SCROLL_Y _______
#define LK_SCROLL_U _______
#define LK_SCROLL_I KC_WH_U
#define LK_SCROLL_O _______
#define LK_SCROLL_P _______
#define LK_SCROLL_LBRC _______
#define LK_SCROLL_RBRC _______
// Middle row
#define LK_SCROLL_CAPS_LOCK _______
#define LK_SCROLL_A _______
#define LK_SCROLL_S KC_WH_L
#define LK_SCROLL_D KC_WH_D
#define LK_SCROLL_F KC_WH_R
#define LK_SCROLL_G _______
#define LK_SCROLL_H _______
#define LK_SCROLL_J KC_WH_L
#define LK_SCROLL_K KC_WH_D
#define LK_SCROLL_L KC_WH_R
#define LK_SCROLL_SC _______
#define LK_SCROLL_QUOTE _______
#define LK_SCROLL_ENTER _______
// Bottom row
#define LK_SCROLL_LSFT _______
#define LK_SCROLL_Z _______
#define LK_SCROLL_X _______
#define LK_SCROLL_C _______
#define LK_SCROLL_V _______
#define LK_SCROLL_B _______
#define LK_SCROLL_N _______
#define LK_SCROLL_M _______
#define LK_SCROLL_LT _______
#define LK_SCROLL_GT _______
#define LK_SCROLL_SL _______
#define LK_SCROLL_RSFT _______
// Thumbs
#define LK_SCROLL_LEFT_THUMB_PRIMARY _______
#define LK_SCROLL_LEFT_THUMB_SECONDARY _______
#define LK_SCROLL_LEFT_THUMB_TERTIARY _______
#define LK_SCROLL_RIGHT_THUMB_PRIMARY _______
#define LK_SCROLL_RIGHT_THUMB_SECONDARY _______
#define LK_SCROLL_RIGHT_THUMB_TERTIARY _______
