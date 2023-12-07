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

// TODO: Markdown

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
#define GOTO_LINK(link) SEND_STRING(FOCUS_URL_NEW_TAB() link /* Delete in case browser auto-fills suggested completion */ SS_TAP(X_DELETE) SS_TAP(X_ENTER))

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


const uint8_t cr_desc_line_moves[] = {
  // Deployability section
  91, 40, 40, 56,
  // Testing section
  51, 226, 123, 99, 79, 83,
  // Testing section
  69, 81, 97, 78,
  // End (move a one line below the last comment so we see the bottom
  // of the details input box).
  // Note: 53 is number of characters to next line, so (presumably) this number
  // brings us three lines below the last one
  53 + 2,
};

uint8_t cr_desc_line_move_idx = 0;
bool cr_desc_line_moving = false;

void setBaseLayerColor(void) {
  rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
  rgb_matrix_set_speed_noeeprom(25);
}

void StartCrDesc(void) {
  rgb_matrix_sethsv_noeeprom(HSV_RED);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_PINWHEEL);
  rgb_matrix_set_speed_noeeprom(200);

  cr_desc_line_moving = true;
  cr_desc_line_move_idx = 0;
}

void EndCrDesc(void) {
  setBaseLayerColor();

  cr_desc_line_moving = false;
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

  if (!cr_desc_line_moving) {
    return false;
  }

  if (cr_desc_line_move_idx >= (sizeof(cr_desc_line_moves)/sizeof(cr_desc_line_moves[0]))) {
    EndCrDesc(); // In case it wasn't ended before
    return false;
  }

  switch (keycode) {
  case CK_CR_DESC:
    SEND_STRING("y");
    break;
  case CK_CR_ID:
    SEND_STRING("n");
    break;
  case CK_MYSTERY:
    SEND_STRING("n/a");
    break;
  default:
    // End the mode, but don't process the key (like alt-mode breaking)
    EndCrDesc();
    return true;
  }

  for (int i = 0; i < cr_desc_line_moves[cr_desc_line_move_idx]; i++) {
    tap_code16(KC_RIGHT);
  }

  cr_desc_line_move_idx++;

  // Check if done
  if (cr_desc_line_move_idx >= (sizeof(cr_desc_line_moves)/sizeof(cr_desc_line_moves[0]))) {
    EndCrDesc();
  }

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
  setBaseLayerColor();
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // LT function can only use
  if (CrDescProcessHandler(keycode, record)) {
    return false;
  }

  if (!record->event.pressed) {
    switch (keycode) {
    case CK_RESET:
      reset_keyboard();
      break;
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

  return true;
}


uint8_t highest_layer = LAYER_BASE;

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t new_highest_layer = get_highest_layer(state);

  if (highest_layer != new_highest_layer) {
    highest_layer = new_highest_layer;

    switch (highest_layer) {
    case LAYER_BASE:
      setBaseLayerColor();
      break;
    case LAYER_ONE:
      rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
      rgb_matrix_mode_noeeprom(RGB_MATRIX_PIXEL_FLOW);
      rgb_matrix_set_speed_noeeprom(150);
      break;
    }
  }

  return state;
}
