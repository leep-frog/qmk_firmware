#include QMK_KEYBOARD_H
#include "version.h"

#include "users/leep-frog/v2/leep_index_v2.h"

#include "users/leep-frog/keyboard-main/leep_index_kb.h"
#include "users/leep-frog/main.h"


// Can't evaluate macro in macro, so use this to ignore bottom row of keyboard
// https://stackoverflow.com/questions/35114050/is-there-a-way-to-force-c-preprocessor-to-evaluate-macro-arguments-before-the-ma
// #define LAYOUT(...) LAYOUT_moonlander(__VA_ARGS__)
// #define BOTTOM_ROW      KC_LCTL, KC_LALT, CK_MUT, CK_MUTS, KC_LCTL, CK_MCR1, CK_MCR2, KC_RCTL, KC_RALT, CK_EYE, KB_OFF, CK_LOCK

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [0] = LAYOUT(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    //     CW_TOGG, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    //     SFT_T(KC_BSPC),KC_A, KC_S, KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RSFT_T(KC_QUOT),
    //     KC_LGUI, ALT_T(KC_Z),KC_X, KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMMA,KC_DOT,  RALT_T(KC_SLSH), KC_RCTL,
    //                             LT(1,KC_ENT), CTL_T(KC_TAB),           SFT_T(KC_BSPC), LT(2,KC_SPC)
    // ),
    [LR_BASE] = LAYOUT(
        CK_LOCK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         TD_Y,    TD_U,    TD_I,    KC_O,    KC_P,    KC_VOLD,
        SC_LSPO, KC_A,    TD_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    TO_OTLK, SC_RSPC,
        KC_LCBR, KC_Z,    KC_X,    TD_C,    TD_V,    TD_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCBR,
                                            TO_SYMB, CK_SHFT,                      TO_ALT,  TO_CTRL
    ),

    [LR_ELLA] = LAYOUT(
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_NO,
        KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCBR,
                                            // These needs to be TO_CTRL/TO_ALT/TO_SYMB (instead of enter/space/tab)
                                            // so that the OSM key + right thumb doesn't trap us in this layer.
                                            TO_SYMB, KC_RSFT,                      TO_ALT,  TO_CTRL
    ),


    [LR_CTRL] = LAYOUT(
        CL(EQL), CL(1),   CL(2),   CL(3),   CL(4),   CL(5),                        CL(6),   CL(7),   CL(8),   CL(9),   CL(0),   _______,
        CL(TAB), CL(Q),   CTRL_W,  KC_END,  CL(R),   CL(T),                        CL(Y),   CK_TABB, CL(I),   CK_TABF, KC_UP,   CL(BSLS),
LSFT_T(CL(LPRN)),KC_HOME, CL(F),   KC_DEL,  KC_RGHT, CK_CTLG,                      KC_BSPC, TGL_SHF, CK_KILL, KC_PGUP, CL(SCLN),RSFT_T(CL(RPRN)),
        CL(LCBR),CL(Z),   TO_CTLX, CK_COPY, KC_PGDN, KC_LEFT,                      KC_DOWN, CL(M),   CL(COMM),CL(DOT), CL(SLSH),CL(RCBR),
                                            TD_CTAB_ALT, CL(ENTER),                CL(SPACE),  _______
    ),

    [LR_CTRL_X] = LAYOUT(
        _______, CL(1),   CL(2),   CL(3),   CL(4),   CL(5),                        CL(6),   CL(7),   CL(8),   CL(9),   CL(0),   _______,
        CL(TAB), CL(Q),   CL(W),   CL(E),   CL(R),   CL(T),                        CK_PSTE, CL(U),   CL(I),   CL(O),   CL(P),   CL(BSLS),
        CL(LPRN),CL(A),   CL(S),   CL(D),   CL(F),   CL(G),                        CL(H),   CL(J),   CL(K),   CL(L),   CL(SCLN),CL(RPRN),
        CL(LCBR),CL(Z),   CL(X),   CL(C),   CL(V),   CL(B),                        CL(N),   CL(M),   CL(COMMA),CL(DOT),CL(SLSH),CL(RCBR),
                                            CL(TAB), CL(ENTER),                    CL(SPACE),  _______
    ),

    [LR_ALT] = LAYOUT(
        AL(EQL), AL(1),   AL(2),   AL(3),   AL(4),   AL(5),                        AL(6),   AL(7),   AL(8),   AL(9),   AL(0),   _______,
        AL(TAB), AL(Q),   AL(F4),  AL(E),   AL(R),   CK_ALTT,                      CK_PSTE, CK_SATB, AL(I),   CK_ATB,  AL(P),   AL(BSLS),
LSFT_T(AL(LPRN)),TD_A,    AL(S),   CL(DEL), CL(RIGHT),AL(G),                       CK_UNBS, AL(J),   AL(K),   AL(L),   AL(SCLN),RSFT_T(AL(RPRN)),
        AL(LCBR),AL(Z),   AL(X),   AL(C),   AL(V),   CL(LEFT),                     AL(N),   AL(M),   AL(COMM),AL(DOT), AL(SLSH),AL(RCBR),
                                            AL(TAB), _______,                      AL(SPACE),  _______
    ),

    // This layer is basically identical to the safe layer aside from the thumb keys.
    [LR_CTRL_ALT] = LAYOUT(
        CK_LOCK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LPRN, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RPRN,
        KC_LCBR, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCBR,
                                            KC_TAB,  KC_RSFT,                      KC_SPACE,KC_ENTER
    ),

//    [LR_SHORTCUTS] = LAYOUT(
//         _______,  _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
//         _______,  _______, _______, KC_ENT,  _______, _______, _______,           _______, KC_WH_U, URL_CPY, KC_MS_U, _______, _______, _______,
//         KC_ENTER, _______, KC_BSPC, KC_DEL,  _______, _______, _______,           _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_RCTL, _______,
//         _______,  _______, _______, _______, _______, GD_BULT,                             CK_NEW,  GD_HD_1, GD_HD_2, GD_HD_3, _______, _______,

//                                                                      BOTTOM_ROW,

//                                            KC_ACL1, KC_ACL0, KC_ACL2,           KC_MS_BTN3, KC_MS_BTN1, KC_MS_BTN2
//     ),

//     [LR_NAVIGATION] = LAYOUT(
//         _______, _______, _______, _______, _______,  _______,     _______,           _______, _______,  _______, _______, _______, _______, _______,
//         _______, _______, CK_WWWB, _______, CK_RST,   RCTL(AL(T)), _______,           _______, SLK_UP,   SLK_UP,  _______, CK_TABF, GU(UP),  CK_ATB,
//         _______, _______, CK_SNIP, TD_CRDC, GU(RGHT), _______,     _______,           _______, SLK_DWN,  SLK_DWN, SLK_JMP, CK_LOGS, MISC_WS, _______,
//         _______, _______, _______, _______, _______,  GU(LEFT),                                GU(DOWN), _______, WS_UP,   WS_DOWN, _______, _______,

//                                                                       BOTTOM_ROW,

//                                             GU(TAB), GU(TAB), _______,           _______, GU(TAB), _______
//     ),

//     [LR_SYMB] = LAYOUT(
//         _______, KC_F1,   KC_F2,   KC_HASH, KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
//         _______, KC_EXLM, KC_COLN, KC_EQL,  KC_CIRC, KC_PIPE, _______,           _______, KC_RPRN, KC_7,    KC_8,    KC_9,    KC_PERC, KC_F12,
//         KC_TAB,  KC_AMPR, KC_ASTR, KC_DLR,  KC_SLSH, KC_LBRC, _______,           _______, CK_MDPS, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMMA,
//         _______, KC_DOT,  KC_COMM, KC_AT,   KC_EQL,  KC_BSLS,                             KC_RCBR, KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
//                                                                       BOTTOM_ROW,
//                                            KC_SPACE, _______, RGB_HUI, TOGGLE_LAYER_COLOR, _______, _______
//     ),

//     [LR_OUTLOOK] = LAYOUT(
//         _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,   _______, _______, _______,
//         _______, _______, _______, SLK_UP,  _______, KC_WH_U, _______,           _______, CL(U),   CL(Q),   CL(COMMA), OL_RLD,  _______, _______,
//         _______, _______, _______, SLK_DWN, SLK_JMP, KC_WH_D, _______,           _______, KC_DEL,  CL(1),   CL(DOT),   CL(2),   _______, _______,
//         _______, _______, _______, _______, _______, _______,                             OL_TDAY, CL(U),   _______,   CL(M),   _______, _______,

//                                                                       BOTTOM_ROW,

//                                             _______, _______, _______,           _______, OL_LEFT, OL_RGHT
//     ),

//     [LR_ONE_HAND_LEFT] = LAYOUT(
//         _______, _______, _______, CK_RST,  _______, _______, _______,           _______, _______, _______,  _______, _______, _______, _______,
//        KC_TAB,   KC_BSPC, CL(W),   CK_SATB, CK_ATB,  CL(T),   _______,           _______, KC_WH_U, URL_CPY,  KC_MS_U, _______, _______, _______,
//        KC_LSFT,  TO_SCRL, CL(R),   CK_TABB, CK_TABF, WS_RGHT, _______,           _______, KC_WH_D, KC_MS_L,  KC_MS_D, KC_MS_R, KC_RCTL, _______,
//        _______,  CK_WWWB, CK_WWWF, OH_COPY, OH_PSTE, _______,                             _______, KC_BTN1,  KC_BTN3, KC_BTN2, _______, _______,

//                                                                       BOTTOM_ROW,

//                                             _______, _______, _______,           CK_ACL, CK_ACL, CK_ACL
//     ),

//     [LR_ONE_HAND_RIGHT] = LAYOUT(
//         _______, _______, _______, _______, _______,  _______, _______,           _______, _______, _______, CK_RST,  _______, _______, _______,
//         _______, _______, _______, KC_MS_U, URL_CPY,  KC_WH_U, _______,           _______, CL(W),   CK_SATB, CK_ATB,  CL(T),   KC_BSPC, KC_TAB,
//         _______, KC_RCTL, KC_MS_L, KC_MS_D, KC_MS_R,  KC_WH_D, _______,           _______, WS_LEFT, CK_TABB, CK_TABF, CL(R),   TO_SCRR, KC_RSFT,
//         _______, _______, KC_BTN2, KC_BTN3, KC_BTN1,  _______,                             _______, _______, CK_WWWB, CK_WWWF, _______, _______,

//                                                                       BOTTOM_ROW,

//                                                 CK_ACL, CK_ACL, CK_ACL,           _______, _______, _______
//     ),

//     [LR_SCROLL] = LAYOUT(
//         _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
//         _______, _______, _______, KC_WH_U, _______, _______, _______,           _______, _______, _______, KC_WH_U, _______, _______, _______,
//         _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,           _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
//         _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,

//                                                                       BOTTOM_ROW,

//                                             _______, _______, _______,           _______, _______, _______
//     ),

//     /*
//     [EMPTY_LAYER] = LAYOUT(
//         _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
//         _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
//         _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
//         _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,

//                                                                       BOTTOM_ROW,

//                                             _______, _______, _______,           _______, _______, _______
//     ),
//     */
};
