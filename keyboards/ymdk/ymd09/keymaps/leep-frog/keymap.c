/*
Copyright 2023
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TODO: For CK_CR_DESC, use exclusively left arrows instead of down to be consistent with editor width.
// TODO: Verify CR_DESC
// TODO: CR_DESC starting position (just first [])
// TODO: Links
// TODO: Markdown

// Note: REPEAT_K does not separate with a comma, whereas FE does
#define REPEAT_0(X)
#define REPEAT_1(X) X
#define REPEAT_2(X) X REPEAT_1(X)
#define REPEAT_3(X) X REPEAT_2(X)
#define REPEAT_4(X) X REPEAT_3(X)
#define REPEAT_5(X) X REPEAT_4(X)
#define REPEAT_6(X) X REPEAT_5(X)
#define REPEAT_7(X) X REPEAT_6(X)
#define REPEAT_8(X) X REPEAT_7(X)
#define REPEAT_9(X) X REPEAT_8(X)
#define REPEAT_10(X) X REPEAT_9(X)
#define REPEAT_11(X) X REPEAT_10(X)

#include QMK_KEYBOARD_H

enum custom_keys {
  START = SAFE_RANGE,
  CK_CR_DESC,
  CK_CR_ID,
  CK_COPY,
  CK_PASTE,
  CK_URL_COPY,
  CK_URL_PASTE,
  CK_RESET,
  CK_MYSTERY,

  LINK_CONDUIT,
  LINK_CRUX,
  LINK_CHIME,
  LINK_MEETINGS,
  LINK_QUIP,
};

#define URL_WAIT_STRING() SS_DELAY(80)
#define FOCUS_URL_TAB() SS_RCTL("l") URL_WAIT_STRING()
#define FOCUS_URL_NEW_TAB() SS_RCTL("t") URL_WAIT_STRING()
#define NTH_URL_ID(k) SS_TAP(X_LEFT) SS_RCTL(REPEAT_##k(SS_TAP(X_RIGHT)) SS_RSFT(SS_TAP(X_RIGHT))) SS_RSFT(SS_TAP(X_LEFT)) SS_RCTL("c")
#define URL_ID(k) SEND_STRING(FOCUS_URL_TAB() NTH_URL_ID(k));
#define URL_CR_ID() URL_ID(6)
#define GOTO_LINK(link) SEND_STRING(FOCUS_URL_NEW_TAB() link SS_TAP(X_ENTER))

void URLWait(void) { wait_ms(80); }

#define NEW_TAB()              \
    SEND_STRING(SS_RCTL("t")); \
    URLWait()

#define URL_COPY()                    \
    SEND_STRING(SS_DOWN(X_RCTL) "l"); \
    URLWait();                        \
    SEND_STRING("c" SS_UP(X_RCTL))

#define URL_PASTE() \
    NEW_TAB();      \
    URLWait();      \
    SEND_STRING(SS_RCTL("v") SS_TAP(X_ENTER));


const uint8_t CK_cr_desc_line_moves[] = {
  // Deployability section
  1, 1, 1, 3,
  // Testing section
  1, 3, 2, 1, 1, 3,
  // Testing section
  1, 1, 1, 3,
  // End (move a few lines below the last comment so we see the bottom
  // of the details input box).
  3,
};

uint8_t CK_cr_desc_line_move_idx = 0;
bool CK_cr_desc_line_moving = false;

void defaultColor(void) {
  rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
  rgb_matrix_set_speed_noeeprom(25);
}

void StartCrDesc(void) {
  rgb_matrix_sethsv_noeeprom(HSV_RED);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_PINWHEEL);
  rgb_matrix_set_speed_noeeprom(200);

  SEND_STRING(
    // Delete 'Revision N'
    REPEAT_7(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_RSFT(SS_TAP(X_END)) SS_TAP(X_BSPC)
    // Go to first entry
    REPEAT_11(SS_TAP(X_DOWN)) SS_TAP(X_HOME) SS_TAP(X_RIGHT)
  );
  CK_cr_desc_line_moving = true;
  CK_cr_desc_line_move_idx = 0;
}

void EndCrDesc(void) {
  defaultColor();

  CK_cr_desc_line_moving = false;
}

bool CrDescHandler(keyrecord_t* record) {
  if (record->event.pressed) {
    StartCrDesc();
  } else {

  }
  return false;
}

bool CrDescProcessHandler(uint16_t keycode, keyrecord_t* record) {
  if (!record->event.pressed) {
    // We want all key unpresses to proceed as normal
    return false;
  }

  if (!CK_cr_desc_line_moving) {
    return false;
  }

  if (CK_cr_desc_line_move_idx >= (sizeof(CK_cr_desc_line_moves)/sizeof(CK_cr_desc_line_moves[0]))) {
    return false;
  }

  switch (keycode) {
  case CK_CR_DESC:
    SEND_STRING("y");
    break;
  case CK_CR_ID:
    SEND_STRING("n");
    break;
  case KC_A:
    SEND_STRING("n/a");
    break;
  default:
    // End the mode, but don't process the key (like alt-mode breaking)
    EndCrDesc();
    return true;
  }

  for (int i = 0; i < CK_cr_desc_line_moves[CK_cr_desc_line_move_idx]; i++) {
    tap_code16(KC_DOWN);
  }
  tap_code16(KC_RIGHT);
  tap_code16(KC_RIGHT);

  CK_cr_desc_line_move_idx++;

  return true;
}

enum layers {
  LAYER_BASE,
  LAYER_ONE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(CK_CR_DESC, CK_CR_ID, CK_MYSTERY,
               CK_COPY, CK_PASTE, RGB_MODE_FORWARD,
               CK_URL_COPY, CK_URL_PASTE, LT(LAYER_ONE, KC_NO)),

  [LAYER_ONE] = LAYOUT(CK_RESET, LINK_CONDUIT, KC_NO,
               LINK_CRUX, LINK_QUIP, KC_NO,
               LINK_CHIME, LINK_MEETINGS, _______),

};

void keyboard_post_init_user(void) {
  SEND_STRING("start");
  defaultColor();
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // LT function can only use
  if (CrDescProcessHandler(keycode, record)) {
    return false;
  }

  if (!record->event.pressed) {
    if (keycode == CK_RESET) {
      reset_keyboard();
    }
    return true;
  }

  switch (keycode) {
  case CK_CR_DESC:
    CrDescHandler(record);
    return false;
    break;
  case CK_CR_ID:
    URL_CR_ID();
    break;
  case CK_COPY:
    SEND_STRING(SS_RCTL("c"));
    break;
  case CK_PASTE:
    SEND_STRING(SS_RCTL("v"));
    break;
  case CK_URL_COPY:
    URL_COPY();
    break;
  case CK_URL_PASTE:
    URL_PASTE();
    break;
  case CK_MYSTERY:
    SEND_STRING("Happy Holidays! From gleeper@ :)");
    break;
  case CK_RESET:
    rgb_matrix_sethsv_noeeprom(HSV_RED);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR );
    break;
  case LINK_CRUX:
    GOTO_LINK("https://code.amazon.com");
    break;
  case LINK_CHIME:
    GOTO_LINK("https://app.chime.aws");
    break;
  case LINK_MEETINGS:
    GOTO_LINK("https://meetings.amazon.com");
    break;
  case LINK_CONDUIT:
    GOTO_LINK("https://conduit.security.a2z.com/accounts");
    break;
  case LINK_QUIP:
    GOTO_LINK("https://quip-amazon.com");
    break;
  default:
    return true;
  }

  return false;
}
