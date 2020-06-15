#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  VRSN = EZ_SAFE_RANGE,
#else
  VRSN = SAFE_RANGE,
#endif
  RGB_SLD
};

// Command descriptions (from https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md)
// LCTL(kc): press left control key and kc command
// LCTL_T(kc): left control when held, kc when tapped
// LGUI: left special (windows or Command button)
// TG(layer): Toggle layer
// LSPO: Left shift when held
// RSPO: Right shift when held

// Custom commands
#define KC_SPCF RCTL(RGUI(KC_RGHT))  // Slide to next workspace
#define KC_SPCB LCTL(LGUI(KC_LEFT))  // Slide to previous workspace
#define KC_TABF RCTL(KC_TAB)  // Next tab in chrome
#define KC_TABB LCTL(LSFT(KC_TAB))  // Previous tab in chrome
#define KC_WWWF LALT(KC_RIGHT)  // Next page in chrome
#define KC_WWWB LALT(KC_LEFT)  // Previous page in chrome
#define MY_COPY LCTL(KC_C)
#define MY_PSTE LCTL(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_EQL,          KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_SPCB,  KC_ESC,   KC_6,    KC_7,    KC_8,        KC_9,        KC_0,    KC_MINUS,
  KC_TAB,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    TG(SYMB), TG(MDIA), KC_Y,    KC_U,    KC_I,        KC_O,        KC_P,    KC_BSLASH,
  KC_LSPO,         KC_A,        KC_S,          KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,        KC_L,        LT(SYMB, KC_SCLN), KC_RSPC,
  KC_LBRACKET,     KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    KC_SPCB,  KC_SPCF,  KC_N,    KC_M,    KC_COMMA,    KC_DOT,      KC_SLSH, KC_RBRACKET,
  KC_LGUI,         KC_QUOTE,    LALT(KC_LSFT), KC_LEFT, MO(SYMB),                                      KC_UP,   KC_DOWN, KC_LBRACKET, KC_RBRACKET, KC_RGUI,

                                                                 KC_SPCF, KC_HOME,                  KC_PGUP, KC_SPCB,
                                                                           KC_END,                  KC_PGDN,
                                                     KC_ENTER, KC_LALT, KC_DELETE,                  KC_BSPACE, KC_RCTRL, KC_SPACE
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  VRSN,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
  _______, KC_EXLM, KC_AT,   KC_EXLM, KC_HASH, KC_AT,   _______,   _______, KC_WH_U, KC_TABB, KC_UP,   KC_TABF, KC_ASTR, KC_F12,
  _______, KC_AMPR, KC_ASTR, KC_DLR,  KC_RPRN, KC_GRV,                      KC_WH_D, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PLUS, _______,
  _______, KC_PERC, KC_CIRC, KC_PERC, KC_CIRC, KC_TILD, _______,   _______, KC_AMPR, KC_1,    KC_2,    KC_3,     KC_BSLS, _______,
  EEP_RST, _______, _______, _______, _______,       _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                               RGB_MOD, _______,     RGB_TOG, RGB_SLD,
                                                        _______,     _______,
                                      RGB_VAD, RGB_VAI, _______,     _______, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox_pretty(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_SPCB, KC_BTN3, KC_SPCF, _______, _______,
  _______, _______, _______, KC_WH_U, _______, _______, _______,     _______, KC_WH_U, KC_TABB, KC_MS_U, KC_TABF, MY_PSTE, _______,
  _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______,                       KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_MPLY,
  _______, _______, _______, _______, _______, _______, _______,     _______, MY_COPY, KC_WWWB, _______, KC_WWWF, _______, _______,
  _______, _______, _______, KC_BTN1, KC_BTN2,                                         KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,

                                               _______, _______,     _______, _______,
                                                        _______,     _______,
                                      _______, _______, _______,     KC_MS_BTN1, KC_RCTRL, KC_MS_BTN2
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};

// Combos
// Remember to increment COMBO_COUNT in config.h when adding to this.
enum combos {
  JK_HYPHEN,
  DF_QUOTE,
  SF_GRAVE,
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sf_combo[] = {KC_S, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [JK_HYPHEN] = COMBO(jk_combo, KC_MINUS),
  [DF_QUOTE] = COMBO(df_combo, KC_QUOTE),
  [SF_GRAVE] = COMBO(sf_combo, KC_GRAVE),
};
