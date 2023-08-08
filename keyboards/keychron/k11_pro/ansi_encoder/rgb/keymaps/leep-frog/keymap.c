/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define LEEP_SAFE_RANGE NEW_SAFE_RANGE

#include "../../../../../../../users/leep-frog/main.c"

// enum layers{
//     MAC_BASE,
//     WIN_BASE,
//     MAC_FN1,
//     WIN_FN1,
//     FN2,
// };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_ELLA] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           KC_SPC,           _______,     _______,       KC_SPC,            KC_RGUI,            KC_LEFT, KC_DOWN, KC_RGHT),

    [LR_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    TD_Y,     TD_U,    TD_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          CK_MCR1,
        SC_LSPO, TD_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     TO_OTLK,  SC_RSPC,  KC_ENT,           CK_MCR2,
        TO_SHCT,           KC_Z,     KC_X,    TD_C,    TD_V,    TD_B,     TD_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  TO_NAVB, KC_UP,
        KC_LCTL, KC_LALT,  TO_SHCT,           TO_SFT,           TO_ALT,            TO_CTRL,          TO_SYMB,            TO_NAV,   KC_LEFT, KB_OFF, CK_LOCK),

    [LR_CTRL] = LAYOUT_69_ansi(
        CL(ESC), CL(1),    CL(2),    CL(3),   CL(4),   CL(5),   CL(6),    CL(7),   CL(8),   CL(9),   CL(0),    CL(MINS), CL(EQL),  CL(BSPC),         CL(INS),
        CL(TAB), CL(Q),    CTRL_W,   KC_END,  CL(R),   TD_CTLT, CL(Y),    CK_TABB, CL(I),   CK_TABF, KC_UP,    CL(LBRC), CL(RBRC), CL(BSLS),         _______,
        CL(LPRN),KC_HOME,  CL(F),    KC_DEL,  KC_RGHT, CK_CTLG,           KC_BSPC, TGL_SHF, CK_KILL, KC_PGUP,  CL(SCLN), CL(RPRN), CL(ENT),          _______,
        CL(LSFT),          CL(Z),    TO_CTLX, CK_COPY, KC_PGDN, KC_LEFT,  KC_LEFT, KC_DOWN, CL(M),   CL(COMM), CL(DOT),  CL(SLSH), CL(RSFT),CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          CL(ENTER),        CL(TAB),           _______,          CL(SPACE),          CL(RGUI), CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_CTRL_X] = LAYOUT_69_ansi(
        CL(ESC), CL(1),    CL(2),    CL(3),   CL(4),   CL(5),   CL(6),    CL(7),   CL(8),   CL(9),   CL(0),    CL(MINS), CL(EQL),  CL(BSPC),         CL(INS),
        CL(TAB), CL(Q),    CL(W),    CL(E),   CL(R),   CL(T),   CL(Y),    CL(U),   CL(I),   CL(O),   CL(P),    CL(LBRC), CL(RBRC), CL(BSLS),         _______,
        CL(CAPS),CL(A),    CL(S),    CL(D),   CL(F),   CL(G),             CL(H),   CL(J),   CL(K),   CL(L),    CL(SCLN), CL(QUOT), CL(ENT),          _______,
        CL(LSFT),          CL(Z),    CL(X),   CL(C),   CL(V),   CL(B),    CL(B),   CL(N),   CL(M),   CL(COMM), CL(DOT),  CL(SLSH), CL(RSFT),CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          CL(ENTER),        CL(TAB),          _______,           CL(SPACE),          CL(RGUI), CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_ALT] = LAYOUT_69_ansi(
        AL(ESC), AL(1),    AL(2),    AL(3),   AL(4),   AL(5),   AL(6),    AL(7),   AL(8),   AL(9),   AL(0),    AL(MINS), AL(EQL),  AL(BSPC),         AL(INS),
        AL(TAB), AL(Q),    AL(F4),   AL(E),   AL(R),   CK_ALTT, CK_PSTE,  CK_SATB, AL(I),   CK_ATB,  AL(P),    AL(LBRC), AL(RBRC), AL(BSLS),         _______,
        AL(LPRN),AL(A),    AL(S),    CL(DEL), CL(RGHT),AL(G),             CK_UNBS, AL(J),   AL(K),   KC_WH_U,  AL(SCLN), AL(RPRN), AL(ENT),          _______,
        AL(LSFT),          AL(Z),    AL(X),   AL(C),   KC_WH_D, CL(LEFT), CL(LEFT),AL(N),   AL(M),   AL(COMM), AL(DOT),  AL(SLSH), AL(RSFT),AL(UP),
        AL(LCTL),AL(LALT), AL(LGUI),          AL(ENTER),        _______,         TO_CTAL,            AL(SPACE),          AL(RGUI), AL(LEFT),AL(DOWN),AL(RGHT)),

    [LR_SYMB] = LAYOUT_69_ansi(
        KC_ESC,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_BSPC,          KC_INS,
        KC_TAB,  KC_EXLM,  KC_COLN,  KC_EQL,  KC_CIRC, KC_PIPE, KC_PIPE,  KC_7,    KC_8,    KC_9,    KC_PERC,  KC_LBRC,  KC_RBRC,  KC_BSLS,          _______,
        KC_CAPS, KC_AMPR,  KC_ASTR,  KC_DLR,  KC_SLSH, KC_LBRC,           CK_MDPS, KC_4,    KC_5,    KC_6,     KC_0,     KC_QUOT,  KC_ENT,           _______,
        KC_LSFT,           KC_TILD,  KC_EXLM, KC_AT,   KC_EQL,  KC_BSLS,  KC_LCBR, KC_RCBR, KC_1,    KC_2,     KC_3,     KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           TO_SFT,           TO_ALT,            TO_CTRL,          TO_SYMB,            KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT),

    // This is currently identical to the LR_NAVIGATION layer.
    [LR_SHORTCUTS] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, TD_RST,  _______, _______,  _______, URL_CRI, _______, GU(UP),   _______,  _______,  _______,          _______,
        _______, _______,  CK_SNIP,  _______, GU(RGHT),_______,           _______, GD_HD_4, GD_HD_5, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, GU(LEFT), GU(LEFT),GU(DOWN),GD_HD_1, GD_HD_2,  GD_HD_3,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    // This is currently identical to the LR_SHORTCUTS layer.
    [LR_NAVIGATION] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, TD_RST,  _______, _______,  _______, URL_CRI, _______, GU(UP),   _______,  _______,  _______,          _______,
        _______, _______,  CK_SNIP,  _______, GU(RGHT),_______,           _______, GD_HD_4, GD_HD_5, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, GU(LEFT), GU(LEFT),GU(DOWN),GD_HD_1, GD_HD_2,  GD_HD_3,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    [LR_OUTLOOK] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______, CL(U),    CL(Q),   CL(COMMA),OL_RLD, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______,           KC_DEL,  CL(1),   CL(DOT), CL(2),    _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  _______, OL_TDAY, CL(U),   _______,  CL(M),    _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    // This layer is currently identical to LR_ONE_HAND_RIGHT
    [LR_ONE_HAND_LEFT] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  CL(W),    CK_SATB, CK_ATB,  TD_CTLT, CL(W),    CK_SATB, CK_ATB,  TD_CTLT, _______,  _______,  _______,  _______,          _______,
        _______, WS_LEFT,  CL(R),    CK_TABB, CK_TABF, WS_RGHT,           WS_LEFT, CK_TABB, CK_TABF, CL(R),    TO_SCRR,  _______,  _______,          _______,
        _______,           CK_WWWB,  CK_WWWF, OH_COPY, OH_PSTE, _______,  _______, OH_COPY, OH_PSTE, CK_WWWB,  CK_WWWF,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    // This layer is currently identical to LR_ONE_HAND_LEFT
    [LR_ONE_HAND_RIGHT] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  CL(W),    CK_SATB, CK_ATB,  TD_CTLT, CL(W),    CK_SATB, CK_ATB,  TD_CTLT, _______,  _______,  _______,  _______,          _______,
        _______, WS_LEFT,  CL(R),    CK_TABB, CK_TABF, WS_RGHT,           WS_LEFT, CK_TABB, CK_TABF, CL(R),    TO_SCRR,  _______,  _______,          _______,
        _______,           CK_WWWB,  CK_WWWF, OH_COPY, OH_PSTE, _______,  _______, OH_COPY, OH_PSTE, CK_WWWB,  CK_WWWF,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    // Need this so that the layer map size is full (as expected by encoder)
    [NUM_LAYERS-1] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),
};

#if defined(ENCODER_MAP_ENABLE)
#define NUM_DIRECTIONS 2
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0 ... NUM_LAYERS - 1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
  [LR_ALT] = { ENCODER_CCW_CW(CL(MINS), CL(EQL))},
};
#endif // ENCODER_MAP_ENABLE
