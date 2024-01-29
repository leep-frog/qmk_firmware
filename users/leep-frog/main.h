#pragma once

#include "users/leep-frog/v2/leep_custom_keycodes_v2.h"

// Note: we don't need to organize by handler type,
// but do so for readability.
// TODO: Change CK prefix to CKE (CK Enum) since these are actually starting at 0 and not SAFE_RANGE (see CK(...)s below for proper values)
enum custom_keycode_handlers {
  // Fn handlers
  TO_ALT_HANDLER,
  TO_CTRL_HANDLER,
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
  MS_CTRL_HANDLER,
  CK_ALTT_HANDLER,
  CK_MUTS_HANDLER,
  CK_MUT_HANDLER,
  CK_CTLG_HANDLER,
  CK_CRDC_HANDLER,
  // String handlers
  CK_UNBS_HANDLER,
  CK_LOGS_HANDLER,
  URL_PST_HANDLER,
  URL_CPY_HANDLER,
  OL_TDAY_HANDLER,
  CK_OSM_SHIFT,

#ifdef LEEP_TEST_MODE
  // CK_TEST_CONFIRM is uesd by tests to confirm that the keyboard
  // is back in a default state
  CK_TEST_CONFIRM,
#endif
};


#define TO_ALT CK(TO_ALT_HANDLER)
#define TO_CTRL CK(TO_CTRL_HANDLER)
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
#define MS_CTRL CK(MS_CTRL_HANDLER)
#define CK_ALTT CK(CK_ALTT_HANDLER)
#define CK_MUTS CK(CK_MUTS_HANDLER)
#define CK_MUT CK(CK_MUT_HANDLER)
#define CK_CTLG CK(CK_CTLG_HANDLER)
#define CK_CRDC CK(CK_CRDC_HANDLER)

#define URL_PST CK(URL_PST_HANDLER)
#define URL_CPY CK(URL_CPY_HANDLER)
#define OL_TDAY CK(OL_TDAY_HANDLER)
#define CK_UNBS CK(CK_UNBS_HANDLER)
#define CK_LOGS CK(CK_LOGS_HANDLER)
#define CK_SHFT CK(CK_OSM_SHIFT)

#ifdef LEEP_TEST_MODE
extern char test_message[];
#define CK_TEST CK(CK_TEST_CONFIRM)
#endif
