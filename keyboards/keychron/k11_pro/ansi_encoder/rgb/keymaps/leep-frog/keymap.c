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

#include "version.h"

#include "users/leep-frog/v2/leep_index_v2.h"

#include "users/leep-frog/keyboard-main/leep_index_kb.h"
#include "users/leep-frog/main.h"


#define LEEP_LAYOUT(PFX, backspace, version, bsls, del, home, up, ctrl, alt, ll_thumb, lm_thumb, lr_thumb, rl_thumb, rm_thumb, rr_thumb, left, down, right) LAYOUT_69_ansi( \
    PFX##_ESC,       PFX##_1,   PFX##_2,   PFX##_3,  PFX##_4,  PFX##_5,  PFX##_6,   PFX##_7,  PFX##_8,  PFX##_9,  PFX##_0,   PFX##_MINUS, PFX##_EQUAL,    backspace,    version, \
    PFX##_TAB,       PFX##_Q,   PFX##_W,   PFX##_E,  PFX##_R,  PFX##_T,  PFX##_Y,   PFX##_U,  PFX##_I,  PFX##_O,  PFX##_P,   PFX##_LBRC,  PFX##_RBRC,     bsls,         del,     \
    PFX##_CAPS_LOCK, PFX##_A,   PFX##_S,   PFX##_D,  PFX##_F,  PFX##_G,             PFX##_H,  PFX##_J,  PFX##_K,  PFX##_L,   PFX##_SC,    PFX##_QUOTE,    PFX##_ENTER,  home,    \
    PFX##_LSFT,      PFX##_Z,   PFX##_X,   PFX##_C,  PFX##_V,  PFX##_B,  PFX##_B ,  PFX##_N,  PFX##_M,  PFX##_LT, PFX##_GT,  PFX##_SL,    PFX##_RSFT,     up,      \
    ctrl,    alt,    ll_thumb,         lm_thumb,        lr_thumb, rl_thumb,          rm_thumb,           rr_thumb,            left, down, right)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LR_ELLA] = LEEP_LAYOUT(LK_ELLA,
        /* number row */ KC_BSPC, CK_VRSN,
        /*  top row   */ KC_BSLS, KC_DEL,
        /* middle row */ KC_HOME,
        /* bottom row */ KC_UP,
        // These needs to be TO_CTRL/TO_ALT/TO_SYMB (instead of enter/space/tab)
        // so that the OSM key + right thumb doesn't trap us in this layer.
        KC_LCTL, KC_LALT,  KC_LGUI,         KC_RSFT,        TO_ALT_KEYCODE, TO_CTRL,          TO_SYMB,           KC_RGUI,            KC_LEFT, KC_DOWN, KC_RGHT),

    [LR_BASE] = LEEP_LAYOUT(LK_BASE,
        /* number row */ KC_BSPC, CK_VRSN,
        /*  top row   */ KC_BSLS, CK_MCR1,
        /* middle row */ CK_MCR2,
        /* bottom row */ CK_LOCK,
        KC_LCTL, KC_LALT,  TO_SHCT,         CK_SHFT,          TO_ALT,       TO_CTRL,       TO_SYMB,          TO_SHCT,            KC_LEFT,  KB_OFF,  KC_RGHT),

    [LR_CTRL] = LEEP_LAYOUT(LK_CTRL,
        /* number row */ CL(BSPC),  _______,
        /*  top row   */ CL(BSLS),   _______,
        /* middle row */ _______,
        /* bottom row */ CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          CL(ENTER),        MO(LR_CTRL_SHIFT),    _______,          CL(SPACE),          CL(RGUI), CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_CTRL_SHIFT] = LEEP_LAYOUT(LK_CTRL_SHIFT,
        /* number row */ _______, _______,
        /*  top row   */ _______, _______,
        /* middle row */ _______,
        /* bottom row */ _______,
        _______, _______,  _______,           _______,      _______,         _______,            _______,          _______, _______,_______,_______),

    [LR_CTRL_X] = LEEP_LAYOUT(LK_CTRL_X,
        /* number row */ CL(BSPC),  _______,
        /*  top row   */ CL(BSLS),   _______,
        /* middle row */ _______,
        /* bottom row */ CL(UP),
        CL(LCTL),CL(LALT), CL(LGUI),          CL(ENTER),        CL(TAB),          _______,           CL(SPACE),          CL(RGUI), CL(LEFT),CL(DOWN),CL(RGHT)),

    [LR_ALT] = LEEP_LAYOUT(LK_ALT,
        /* number row */ AL(BSPC),  _______,
        /*  top row   */ AL(BSLS),   _______,
        /* middle row */ _______,
        /* bottom row */ AL(UP),
        AL(LCTL),AL(LALT), _______,           AL(ENTER),      _______,         AL(ENTER),            _______,          AL(RGUI), AL(LEFT),AL(DOWN),AL(RGHT)),

    [LR_SYMB] = LEEP_LAYOUT(LK_SYMB,
        /* number row */ KC_BSPC, _______,
        /*  top row   */ KC_BSLS, _______,
        /* middle row */ _______,
        /* bottom row */ KC_UP,
        KC_LCTL, KC_LALT,  _______,           KC_ENTER,         KC_SPACE,          KC_ENTER,         _______,            KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT),

    // This is currently identical to the LR_NAVIGATION layer.
    [LR_SHORTCUTS] = LEEP_LAYOUT(LK_SHORTCUTS,
        /* number row */ _______, _______,
        /*  top row   */ _______, _______,
        /* middle row */ _______,
        /* bottom row */ _______,
        _______, _______,  _______,           _______,          GU(TAB),           _______,          _______,            _______,  _______, _______, _______),

    [LR_OUTLOOK] = LEEP_LAYOUT(LK_OUTLOOK,
        /* number row */ _______, _______,
        /*  top row   */ _______, _______,
        /* middle row */ _______,
        /* bottom row */ _______,
        _______, _______,  _______,           _______,          _______,           OL_LEFT,          OL_RGHT,            _______,  _______, _______, _______),

    [LR_ONE_HAND] = LEEP_LAYOUT(LK_ONE_HAND,
        /* number row */ _______, _______,
        /*  top row   */ _______, _______,
        /* middle row */ _______,
        /* bottom row */ _______,
        _______, _______,  _______,           _______,          _______,           _______,          _______,            _______,  _______, _______, _______),

    // Need this so that the layer map size is full (as expected by encoder)
    [LR_SCROLL] = LAYOUT_69_ansi(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  KC_WH_U, _______, _______, _______,  _______, KC_WH_U, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  KC_WH_L,  KC_WH_D, KC_WH_R, _______,           _______, KC_WH_L, KC_WH_D, KC_WH_R,  _______,  _______,  _______,          _______,
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
