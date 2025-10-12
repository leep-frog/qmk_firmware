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

// LR_ELLA layer
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

#define YOK(x) x
#define UGH() KC_1, KC_2

#define LK_ELLA_00 LK_ELLA_1, LK_ELLA_2, LK_ELLA_3, LK_ELLA_4, LK_ELLA_5
#define LK_ELLA_01 LK_ELLA_6, LK_ELLA_7, LK_ELLA_8, LK_ELLA_9, LK_ELLA_0
#define LK_ELLA_10 LK_ELLA_Q, LK_ELLA_W, LK_ELLA_E, LK_ELLA_R, LK_ELLA_T
#define LK_ELLA_11 LK_ELLA_Y, LK_ELLA_U, LK_ELLA_I, LK_ELLA_O, LK_ELLA_P
#define LK_ELLA_20 LK_ELLA_A, LK_ELLA_S, LK_ELLA_D, LK_ELLA_F, LK_ELLA_G
#define LK_ELLA_21 LK_ELLA_H, LK_ELLA_J, LK_ELLA_K, LK_ELLA_L, LK_ELLA_SC
#define LK_ELLA_30 LK_ELLA_Z, LK_ELLA_X, LK_ELLA_C, LK_ELLA_V, LK_ELLA_B
#define LK_ELLA_31 LK_ELLA_N, LK_ELLA_M, LK_ELLA_LT, LK_ELLA_GT, LK_ELLA_SL

// LR_BASE layer
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
#define LK_BASE_CAPS_LOCK LSFT_T(KC_LPRN)
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

#define LK_BASE_00 LK_BASE_1, LK_BASE_2, LK_BASE_3, LK_BASE_4, LK_BASE_5
#define LK_BASE_01 LK_BASE_6, LK_BASE_7, LK_BASE_8, LK_BASE_9, LK_BASE_0
#define LK_BASE_10 LK_BASE_Q, LK_BASE_W, LK_BASE_E, LK_BASE_R, LK_BASE_T
#define LK_BASE_11 LK_BASE_Y, LK_BASE_U, LK_BASE_I, LK_BASE_O, LK_BASE_P
#define LK_BASE_20 LK_BASE_A, LK_BASE_S, LK_BASE_D, LK_BASE_F, LK_BASE_G
#define LK_BASE_21 LK_BASE_H, LK_BASE_J, LK_BASE_K, LK_BASE_L, LK_BASE_SC
#define LK_BASE_30 LK_BASE_Z, LK_BASE_X, LK_BASE_C, LK_BASE_V, LK_BASE_B
#define LK_BASE_31 LK_BASE_N, LK_BASE_M, LK_BASE_LT, LK_BASE_GT, LK_BASE_SL


// LR_CTRL layer
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
#define LK_CTRL_QUOTE MO(LR_CTRL_SHIFT)
#define LK_CTRL_ENTER CL(ENT)
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

#define LK_CTRL_00 LK_CTRL_1, LK_CTRL_2, LK_CTRL_3, LK_CTRL_4, LK_CTRL_5
#define LK_CTRL_01 LK_CTRL_6, LK_CTRL_7, LK_CTRL_8, LK_CTRL_9, LK_CTRL_0
#define LK_CTRL_10 LK_CTRL_Q, LK_CTRL_W, LK_CTRL_E, LK_CTRL_R, LK_CTRL_T
#define LK_CTRL_11 LK_CTRL_Y, LK_CTRL_U, LK_CTRL_I, LK_CTRL_O, LK_CTRL_P
#define LK_CTRL_20 LK_CTRL_A, LK_CTRL_S, LK_CTRL_D, LK_CTRL_F, LK_CTRL_G
#define LK_CTRL_21 LK_CTRL_H, LK_CTRL_J, LK_CTRL_K, LK_CTRL_L, LK_CTRL_SC
#define LK_CTRL_30 LK_CTRL_Z, LK_CTRL_X, LK_CTRL_C, LK_CTRL_V, LK_CTRL_B
#define LK_CTRL_31 LK_CTRL_N, LK_CTRL_M, LK_CTRL_LT, LK_CTRL_GT, LK_CTRL_SL

// LR_CTRL_X layer
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
#define LK_CTRL_X_CAPS_LOCK CL(LSFT)
#define LK_CTRL_X_A CL(A)
#define LK_CTRL_X_S CL(F)
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

#define LK_CTRL_X_00 LK_CTRL_X_1, LK_CTRL_X_2, LK_CTRL_X_3, LK_CTRL_X_4, LK_CTRL_X_5
#define LK_CTRL_X_01 LK_CTRL_X_6, LK_CTRL_X_7, LK_CTRL_X_8, LK_CTRL_X_9, LK_CTRL_X_0
#define LK_CTRL_X_10 LK_CTRL_X_Q, LK_CTRL_X_W, LK_CTRL_X_E, LK_CTRL_X_R, LK_CTRL_X_T
#define LK_CTRL_X_11 LK_CTRL_X_Y, LK_CTRL_X_U, LK_CTRL_X_I, LK_CTRL_X_O, LK_CTRL_X_P
#define LK_CTRL_X_20 LK_CTRL_X_A, LK_CTRL_X_S, LK_CTRL_X_D, LK_CTRL_X_F, LK_CTRL_X_G
#define LK_CTRL_X_21 LK_CTRL_X_H, LK_CTRL_X_J, LK_CTRL_X_K, LK_CTRL_X_L, LK_CTRL_X_SC
#define LK_CTRL_X_30 LK_CTRL_X_Z, LK_CTRL_X_X, LK_CTRL_X_C, LK_CTRL_X_V, LK_CTRL_X_B
#define LK_CTRL_X_31 LK_CTRL_X_N, LK_CTRL_X_M, LK_CTRL_X_LT, LK_CTRL_X_GT, LK_CTRL_X_SL


// LR_ALT layer
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

#define LK_ALT_00 LK_ALT_1, LK_ALT_2, LK_ALT_3, LK_ALT_4, LK_ALT_5
#define LK_ALT_01 LK_ALT_6, LK_ALT_7, LK_ALT_8, LK_ALT_9, LK_ALT_0
#define LK_ALT_10 LK_ALT_Q, LK_ALT_W, LK_ALT_E, LK_ALT_R, LK_ALT_T
#define LK_ALT_11 LK_ALT_Y, LK_ALT_U, LK_ALT_I, LK_ALT_O, LK_ALT_P
#define LK_ALT_20 LK_ALT_A, LK_ALT_S, LK_ALT_D, LK_ALT_F, LK_ALT_G
#define LK_ALT_21 LK_ALT_H, LK_ALT_J, LK_ALT_K, LK_ALT_L, LK_ALT_SC
#define LK_ALT_30 LK_ALT_Z, LK_ALT_X, LK_ALT_C, LK_ALT_V, LK_ALT_B
#define LK_ALT_31 LK_ALT_N, LK_ALT_M, LK_ALT_LT, LK_ALT_GT, LK_ALT_SL

// LR_SYMB layer
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
#define LK_SYMB_CAPS_LOCK KC_LSFT
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
#define LK_SYMB_QUOTE KC_COMMA
#define LK_SYMB_ENTER KC_ENTER
#define LK_SYMB_LSFT KC_LSFT
#define LK_SYMB_Z KC_EQUAL
#define LK_SYMB_X KC_UNDERSCORE
#define LK_SYMB_C KC_LBRC
#define LK_SYMB_V CK_MDPS
#define LK_SYMB_B _______
#define LK_SYMB_N KC_BSLS
#define LK_SYMB_M KC_PIPE
#define LK_SYMB_LT KC_COMM
#define LK_SYMB_GT KC_DOT
#define LK_SYMB_SL KC_SLSH
#define LK_SYMB_RSFT KC_RBRC

#define LK_SYMB_00 LK_SYMB_1, LK_SYMB_2, LK_SYMB_3, LK_SYMB_4, LK_SYMB_5
#define LK_SYMB_01 LK_SYMB_6, LK_SYMB_7, LK_SYMB_8, LK_SYMB_9, LK_SYMB_0
#define LK_SYMB_10 LK_SYMB_Q, LK_SYMB_W, LK_SYMB_E, LK_SYMB_R, LK_SYMB_T
#define LK_SYMB_11 LK_SYMB_Y, LK_SYMB_U, LK_SYMB_I, LK_SYMB_O, LK_SYMB_P
#define LK_SYMB_20 LK_SYMB_A, LK_SYMB_S, LK_SYMB_D, LK_SYMB_F, LK_SYMB_G
#define LK_SYMB_21 LK_SYMB_H, LK_SYMB_J, LK_SYMB_K, LK_SYMB_L, LK_SYMB_SC
#define LK_SYMB_30 LK_SYMB_Z, LK_SYMB_X, LK_SYMB_C, LK_SYMB_V, LK_SYMB_B
#define LK_SYMB_31 LK_SYMB_N, LK_SYMB_M, LK_SYMB_LT, LK_SYMB_GT, LK_SYMB_SL


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
