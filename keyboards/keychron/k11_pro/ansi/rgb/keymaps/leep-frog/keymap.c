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
        KC_LCTL, KC_LALT,  KC_LGUI,           KC_SPC,           _______,     _______,       KC_SPC,            KC_RGUI,           KC_LEFT, KC_DOWN, KC_RGHT),

    [LR_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           TO_SFT,           TO_ALT,      TO_CTRL,       TO_SYMB,           KC_RGUI,           KC_LEFT, KC_DOWN, KC_RGHT),

    [LR_CTRL] = LAYOUT_69_ansi(
        CL(ESC), CL(1),    CL(2),    CL(3),   CL(4),   CL(5),   CL(6),    CL(7),   CL(8),   CL(9),   CL(0),    CL(MINS), CL(EQL),  CL(BSPC),         CL(INS),
        CL(TAB), CL(Q),    CTRL_W,   KC_END,  CL(R),   TD_CTLT, CL(Y),    CK_TABB, CL(I),   CK_TABF, KC_UP,    CL(LBRC), CL(RBRC), CL(BSLS),         CL(DEL),
        CL(CAPS),KC_HOME,  CL(F),    KC_DEL,  KC_RGHT, CK_CTLG,           KC_BSPC, TGL_SHF, CK_KILL, KC_PGUP,  CL(SCLN), CL(QUOT), CL(ENT),          CL(HOME),
        CL(LSFT),          CL(Z),    TO_CTLX, CK_COPY, KC_PGDN, KC_LEFT,  KC_LEFT, KC_DOWN, CL(M),   CL(COMM), CL(DOT),  CL(SLSH), CL(RSFT),CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          TO_SFT,           TO_ALT,      TO_CTRL,       TO_SYMB,           CL(RGUI),          CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_CTRL_X] = LAYOUT_69_ansi(
        CL(ESC), CL(1),    CL(2),    CL(3),   CL(4),   CL(5),   CL(6),    CL(7),   CL(8),   CL(9),   CL(0),    CL(MINS), CL(EQL),  CL(BSPC),         CL(INS),
        CL(TAB), CL(Q),    CL(W),    CL(E),   CL(R),   CL(T),   CL(Y),    CL(U),   CL(I),   CL(O),   CL(P),    CL(LBRC), CL(RBRC), CL(BSLS),         CL(DEL),
        CL(CAPS),CL(A),    CL(S),    CL(D),   CL(F),   CL(G),             CL(H),   CL(J),   CL(K),   CL(L),    CL(SCLN), CL(QUOT), CL(ENT),          CL(HOME),
        CL(LSFT),          CL(Z),    CL(X),   CL(C),   CL(V),   CL(B),    CL(B),   CL(N),   CL(M),   CL(COMM), CL(DOT),  CL(SLSH), CL(RSFT),CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          TO_SFT,           TO_ALT,      TO_CTRL,       TO_SYMB,           CL(RGUI),          CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_ALT] = LAYOUT_69_ansi(
        AL(ESC), AL(1),    AL(2),    AL(3),   AL(4),   AL(5),   AL(6),    AL(7),   AL(8),   AL(9),   AL(0),    AL(MINS), AL(EQL),  AL(BSPC),         AL(INS),
        AL(TAB), AL(Q),    AL(W),    AL(E),   AL(R),   AL(T),   AL(Y),    AL(U),   AL(I),   AL(O),   AL(P),    AL(LBRC), AL(RBRC), AL(BSLS),         AL(DEL),
        AL(CAPS),AL(A),    AL(S),    AL(D),   AL(F),   AL(G),             AL(H),   AL(J),   AL(K),   AL(L),    AL(SCLN), AL(QUOT), AL(ENT),          AL(HOME),
        AL(LSFT),          AL(Z),    AL(X),   AL(C),   AL(V),   AL(B),    AL(B),   AL(N),   AL(M),   AL(COMM), AL(DOT),  AL(SLSH), AL(RSFT),AL(UP),
        AL(LCTL),AL(LALT), AL(LGUI),          TO_SFT,           TO_ALT,      TO_CTRL,       TO_SYMB,           AL(RGUI),          AL(LEFT),AL(DOWN),AL(RGHT)),
};
