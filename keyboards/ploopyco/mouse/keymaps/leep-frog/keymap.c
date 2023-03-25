/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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
#include "leep_enum.c"
#include "leep_url.c"
#include "leep_tap_dance.c"
#include "leep_alt.c"
#include "leep_layers.c"
#include "leep_outlook.c"


/*************************
 * TODO:
 * Ctrl-f
 * Escape
 * Enter
 * Backspace
 **************************/

/*******************
 * Notes:
 * C(kc) -> LCTL(kc)
 * A(kc) -> LALT(kc)
 * S(kc) -> LSFT(kc)
 * G(kc) -> LGUI(kc)
 ********************/

// Just switch forward and back keys
#define LEEPOUT(C1, C2, C3, C4, C5, C6, C7, C8) LAYOUT(C1, C2, C3, C4, C5, C7, C6, C8)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Example format:
    [LR_ABC] = LEEPOUT(
        // Top buttons
        far_left, left, wheel_click, right, far_right,
        // Side buttons
        forward, back,
        // Special button
        rectangle
    ),
    */

    [LR_BASE] = LEEPOUT(
        // Top
        KC_BTN1, TO_CTRL, KC_BTN3, TO_ALT, TO_WS,
        // Side buttons
        TD_COPY, TD_PASTE,
        // Special button
        QK_BOOT),

    // This layer holds down the ctrl key when activated (mostly so ctrl+click works properly).
    // As pressing ctrl+click in too rapid succession doesn't always work on the work laptop.
    [LR_CTRL] = LEEPOUT(
        // Top
        KC_BTN1, _______, KC_BTN1, KC_TAB, TD_CTAB,
        // Side buttons
        S(KC_TAB), TD_OTAB,
        // Special button
        _______),

    [LR_ALT] = LEEPOUT(
        // Top
        _______, CK_ATAB, _______, _______, LT(LR_OUTLOOK, _______),
        // Side buttons
        CK_SATAB, _______,
        // Special button
        _______),

    [LR_WS] = LEEPOUT(
        // Top
        _______, C(G(KC_LEFT)), _______, C(G(KC_RIGHT)), _______,
        // Side buttons
        _______, _______,
        // Special button
        _______),

    [LR_KB] = LEEPOUT(
        // Top
        _______, KC_BSPC, _______, KC_DEL, KC_ENTER,
        // Side buttons
        _______, _______,
        // Special button
        _______),

    [LR_OUTLOOK] = LEEPOUT(
        // Top
        _______, KC_BTN1, _______, OL_DEL, _______,
        // Side buttons
        OL_READ, OL_UNRD,
        // Special button
        _______),
};

// https://docs.qmk.fm/#/feature_pointing_device?id=manipulating-mouse-reports
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report){
    // executed each time the sensor is updated
    // mouse_report.<attribute> - can be used to access indivdual mouse attributes
    if (IS_LAYER_ON(LR_WS)) {
        /*int v = mouse_report->v;
        mouse_report->v = mouse_report->h;
        mouse_report->h = v;*/

        /*mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;*/

        mouse_report.h = mouse_report.v;
        mouse_report.v = 0;


        /*int8_t v = mouse_report.v;
        mouse_report.v = mouse_report.h;
        mouse_report.h = v;*/
    }

    mouse_report.v = 0;
    mouse_report.h = 0;
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return true;
    }

    if (alt_is_active() && keycode != CK_ATAB && keycode != CK_SATAB) {
        deactivate_alt();
        return false;
    }

    switch (keycode) {
        // Custom keycodes (in order for performance)
        case CK_ATAB:
            activate_alt();
            SEND_STRING(SS_TAP(X_TAB));
            return true;
        case CK_SATAB:
            activate_alt();
            SEND_STRING(SS_RSFT(SS_TAP(X_TAB)));
            return true;
        case OL_TDAY:
            SEND_STRING(SS_RALT(SS_TAP(X_H)) SS_TAP(X_O) SS_TAP(X_D));
            return true;
    }

    return true;
}
