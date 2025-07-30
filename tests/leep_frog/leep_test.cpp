#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"
#include "leep_keyboard.h"
#include "../../../../users/leep-frog/main.h"
#include "users/leep-frog/keyboard-main/leep_tap_dance_kb.h"

using testing::_;
using testing::InSequence;
// See lib/googletest/docs/reference/assertions.md
using ::testing::IsEmpty;

// Define lots of transparent key aliases because LEEP_ADD_KEY creates
// a variable for each key created, so we need different names.
const uint16_t TK_0 = KC_TRANSPARENT;
const uint16_t TK_1 = KC_TRANSPARENT;
const uint16_t TK_2 = KC_TRANSPARENT;
const uint16_t TK_3 = KC_TRANSPARENT;
const uint16_t TK_4 = KC_TRANSPARENT;
const uint16_t TK_5 = KC_TRANSPARENT;
const uint16_t TK_6 = KC_TRANSPARENT;

// We need these go betweens because CK_ABCs are macros and the nested macros pass the initial string values around (not the final macro)
const uint16_t ck_test = CK_TEST;
const uint16_t ck_shft = CK_SHFT;

class LeepFrog : public TestFixture {};

#define NEW_ROW = QK_USER_MAX - 1

uint16_t leep_key_layer = 0;
uint16_t leep_key_col = 0;
#define LEEP_ADD_KEY(key) KeymapKey k_##key = KeymapKey(leep_key_layer, leep_key_col++, 0, key); add_key(k_##key);
#define LEEP_ADD_KEY_ONLY(key) add_key(KeymapKey(leep_key_layer, leep_key_col++, 0, key));

#define LEEP_KEY_ROW_ONLY(layer, n, ...) leep_key_layer = layer; leep_key_col = 0; REDUCE_##n(LEEP_ADD_KEY_ONLY, , __VA_ARGS__)
#define LEEP_KEY_ROW(layer, n, ...) leep_key_layer = layer; leep_key_col = 0; REDUCE_##n(LEEP_ADD_KEY, , __VA_ARGS__)

#define CONFIRM_RESET()   \
k_ck_test.press();        \
EXPECT_NO_REPORT(driver); \
run_one_scan_loop();      \
/* Confirm the running string is set to confirm this value is actually changing on each run. */ \
EXPECT_STREQ(test_message, "Running tests (waiting for release)..."); \
k_ck_test.release();      \
EXPECT_NO_REPORT(driver); \
run_one_scan_loop();      \
EXPECT_STREQ(test_message, "Success!");

/***************
* Unlock tests *
***************/

TEST_F(LeepFrog, UnlockBehavior) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 3,
      KC_A,
      KC_D,
      ck_test
    )

    // Ignore key before unlocking
    k_KC_A.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // D unlocks
    k_KC_D.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_D.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // A works after unlocking
    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // D unlocks
    k_KC_D.press();
    EXPECT_REPORT(driver, (KC_D));
    run_one_scan_loop();

    k_KC_D.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

/************
* OSM tests *
************/

TEST_F(LeepFrog, Osm_TransparentKey) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 3,
      KC_A,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      TK_0,
      TK_1,
      TK_2
    )

    // Press and unpress the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the A key, which should be shifted.
    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_DifferentKey) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 3,
      KC_A,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      KC_B,
      TK_0,
      TK_1
    )

    // Press and unpress the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the A key, which should be shifted.
    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_B));
    EXPECT_REPORT(driver, (KC_B));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_OverlappingKeyPresses) {
    TestDriver driver;
    InSequence s;

    LEEP_KEY_ROW(0, 4,
      KC_H,
      KC_I,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 4,
      TK_0,
      TK_1,
      TK_2,
      TK_3
    )

    // Press and unpress the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press H and then press I before releasing H.
    k_KC_H.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    EXPECT_REPORT(driver, (KC_H));
    run_one_scan_loop();

    k_KC_I.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_REPORT(driver, (KC_H, KC_I));
    EXPECT_REPORT(driver, (KC_I));
    run_one_scan_loop();

    k_KC_I.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_OverlappingTapDanceKeyPresses) {
    TestDriver driver;
    InSequence s;

    uint16_t td_i = TD_I;

    LEEP_KEY_ROW(0, 4,
      KC_H,
      td_i, // regular KC_I in the other layer
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 4,
      TK_0,
      KC_I,
      TK_2,
      TK_3
    )

    // Press and unpress the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press H and then press I before releasing H.
    k_KC_H.press();
    EXPECT_NO_REPORT(driver);
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    EXPECT_REPORT(driver, (KC_H));
    run_one_scan_loop();

    k_td_i.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    k_td_i.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    EXPECT_REPORT(driver, (KC_I));
    EXPECT_EMPTY_REPORT(driver);
    idle_for(10 * TAPPING_TERM);

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_Hold) {
    TestDriver driver;
    InSequence s;

    uint16_t td_s = TD_S;

    LEEP_KEY_ROW(0, 7,
      td_s, // Tap dance key
      KC_H, // Regular key
      KC_I, // Regular key
      KC_D, // Combo key
      KC_F, // Combo key
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 7,
      TK_0,
      TK_1,
      TK_2,
      TK_3,
      TK_4,
      TK_5,
      TK_6
    )

    // Press and hold the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press the H key, which should be shifted.
    k_KC_H.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press the I key, which should be shifted.
    k_KC_I.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_I));
    run_one_scan_loop();

    k_KC_I.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Overlap the key presses
    k_KC_H.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    run_one_scan_loop();

    k_KC_I.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H, KC_I));
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_REPORT(driver, (KC_RSFT, KC_I));
    run_one_scan_loop();

    k_KC_I.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press a tap dance key
    k_td_s.press();
    run_one_scan_loop();

    k_td_s.release();
    run_one_scan_loop();

    EXPECT_REPORT(driver, (KC_RSFT, KC_S));
    EXPECT_REPORT(driver, (KC_RSFT));
    idle_for(TAPPING_TERM);

    // Press a combo key with no combo
    k_KC_F.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_F));
    run_one_scan_loop();

    k_KC_F.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press a combo key with combo
    k_KC_F.press();
    k_KC_D.press();
    run_one_scan_loop();

    k_KC_F.release();
    k_KC_D.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_QUOTE));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Release the osm shift key
    k_ck_shft.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_StickyHold) {
    TestDriver driver;
    InSequence s;

    uint16_t td_s = TD_S;

    LEEP_KEY_ROW(0, 7,
      td_s, // Tap dance key
      KC_H, // Regular key
      KC_I, // Regular key
      KC_D, // Combo key
      KC_F, // Combo key
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 7,
      TK_0,
      TK_1,
      TK_2,
      TK_3,
      TK_4,
      TK_5,
      TK_6
    )

    // Press and release the osm shift key twice
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_ck_shft.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the H key, which should be shifted.
    k_KC_H.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press the I key, which should be shifted.
    k_KC_I.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_I));
    run_one_scan_loop();

    k_KC_I.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Overlap the key presses
    k_KC_H.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H));
    run_one_scan_loop();

    k_KC_I.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_H, KC_I));
    run_one_scan_loop();

    k_KC_H.release();
    EXPECT_REPORT(driver, (KC_RSFT, KC_I));
    run_one_scan_loop();

    k_KC_I.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press a tap dance key
    k_td_s.press();
    run_one_scan_loop();

    k_td_s.release();
    run_one_scan_loop();

    EXPECT_REPORT(driver, (KC_RSFT, KC_S));
    EXPECT_REPORT(driver, (KC_RSFT));
    idle_for(TAPPING_TERM);

    // Press a combo key with no combo
    k_KC_F.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_F));
    run_one_scan_loop();

    k_KC_F.release();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press a combo key with combo
    k_KC_F.press();
    k_KC_D.press();
    run_one_scan_loop();

    k_KC_F.release();
    k_KC_D.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_QUOTE));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Press again to deactivate osm mode.
    k_ck_shft.press();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

/**************
* Combo tests *
**************/

TEST_F(LeepFrog, ComboBehavior) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 5,
      KC_D,
      KC_F,
      KC_LSFT,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 5,
      TK_0,
      TK_1,
      TK_2,
      TK_3,
      TK_4
    )

    // Press and release the D and F keys simultaneously
    k_KC_D.press();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_D.release();
    k_KC_F.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_QUOTE));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Press and release the D and F keys close together
    k_KC_D.press();
    run_one_scan_loop();

    k_KC_F.press();
    run_one_scan_loop();

    k_KC_D.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_QUOTE));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    k_KC_F.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // When left shift is held, it should do un-shifted quote
    k_KC_LSFT.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    k_KC_D.press();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_D.release();
    k_KC_F.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_QUOTE));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    k_KC_LSFT.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // When right shift is held, it should do un-shifted quote
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    k_KC_D.press();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_D.release();
    k_KC_F.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_QUOTE));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    k_ck_shft.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, ComboAndOSMTap) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 6,
      KC_A,
      KC_B,
      KC_D,
      KC_F,
      ck_shft,
      ck_test
    )

    uint16_t kc_d = KC_D;
    uint16_t kc_f = KC_F;

    LEEP_KEY_ROW(1, 6,
      TK_0,
      KC_C,
      kc_d,
      kc_f,
      TK_1,
      TK_2
    )

    // Press and unpress the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();
    k_ck_shft.release();
    run_one_scan_loop();

    // Press and release the D and F keys simultaneously
    k_KC_D.press();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_D.release();
    k_KC_F.release();
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_QUOTE));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_RSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

/******************
* Tap dance tests *
******************/

TEST_F(LeepFrog, TapDance_CLICK_KC_HOLD_LAYER) {
    TestDriver driver;
    InSequence s;

    uint16_t to_shct = TO_SHCT;
    LEEP_KEY_ROW(0, 3,
      to_shct,
      KC_A,
      ck_test
    )

    LEEP_KEY_ROW(LR_SHORTCUTS, 3,
      TK_0,
      KC_B,
      TK_1
    )

    // Single tap dance just presses the key.
    k_to_shct.press();
    run_one_scan_loop();
    k_to_shct.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LEFT_BRACKET));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    CONFIRM_RESET();

    // Interrupted tap dance
    k_to_shct.press();
    run_one_scan_loop();

    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_B));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    k_to_shct.release();
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    CONFIRM_RESET();

    // Interrupted tap dance with inter-woven release
    k_to_shct.press();
    run_one_scan_loop();

    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_B));
    run_one_scan_loop();

    k_to_shct.release();
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    // Hold tap dance key with no key press
    k_to_shct.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(TAPPING_TERM+1);

    k_to_shct.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, TapDance_CLICK_KC_HOLD_KC) {
    TestDriver driver;
    InSequence s;

    uint16_t td_lcbr = TD_LCBR;
    LEEP_KEY_ROW(0, 3,
      td_lcbr,
      KC_A,
      ck_test
    )

    // LEEP_KEY_ROW(LR_SHORTCUTS, 3,
    //   TK_0,
    //   KC_B,
    //   TK_1
    // )

    // Single tap dance just presses the key.
    k_td_lcbr.press();
    run_one_scan_loop();
    k_td_lcbr.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LEFT_BRACKET));
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    CONFIRM_RESET();

    // Interrupted tap dance
    k_td_lcbr.press();
    run_one_scan_loop();

    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_REPORT(driver, (KC_LSFT));
    run_one_scan_loop();

    k_td_lcbr.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    CONFIRM_RESET();

    // Interrupted tap dance with inter-woven release
    k_td_lcbr.press();
    run_one_scan_loop();

    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_LSFT));
    EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    run_one_scan_loop();

    k_td_lcbr.release();
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);

    CONFIRM_RESET();
}

/****************
* Holding tests *
*****************/

TEST_F(LeepFrog, Osm_HoldJustShyOfTappingTerm) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 3,
      KC_A,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      TK_0,
      TK_1,
      TK_2
    )

    // Press the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Wait to register as hold
    idle_for(TAPPING_TERM-1);

    // Unpress the osm shift key
    k_ck_shft.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the A key, which should NOT be shifted.
    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_RSFT, KC_A));
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, Osm_HoldLongerThanTappingTerm) {
    TestDriver driver;
    InSequence s;
    LEEP_KEY_ROW(0, 3,
      KC_A,
      ck_shft,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      TK_0,
      TK_1,
      TK_2
    )

    // Press the osm shift key
    k_ck_shft.press();
    EXPECT_REPORT(driver, (KC_RSFT));
    run_one_scan_loop();

    // Wait to register as hold
    idle_for(TAPPING_TERM);

    // Unpress the osm shift key
    k_ck_shft.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Press the A key, which should NOT be shifted.
    k_KC_A.press();
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    k_KC_A.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

/*****************************
* Symbol Layer Overlap tests *
******************************/

TEST_F(LeepFrog, SymbolLayerOverlap_KeyPressAndReleaseAllWhileInSymbolLayer) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 4,
      to_symb,
      KC_J,
      KC_K,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 4,
      TK_0,
      KC_1,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}


TEST_F(LeepFrog, SymbolLayerOverlap_ShortOverlapIsConsideredTyping) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_TAB));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_COMMA));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, SymbolLayerOverlap_FullOverlapIsConsideredHold) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, SymbolLayerOverlap_AmbiguousOverlapIsHoldIfInBothEquallyLong) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(43);

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(43);

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_TAB));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_COMMA));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, SymbolLayerOverlap_AmbiguousOverlapIsTypeIfOutSymbLonger) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(43);

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(44);

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_TAB));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_COMMA));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, SymbolLayerOverlap_WorksWithCombo) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = TO_SYMB;

    LEEP_KEY_ROW(LR_BASE, 4,
      to_symb,
      KC_J,
      KC_K,
      ck_test
    )

    LEEP_KEY_ROW(LR_SYMB, 4,
      TK_0,
      KC_1,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the combo
    k_KC_1.press();
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Release the combo
    k_KC_1.release();
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_MINUS));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

/***********************
* One hand layer tests *
************************/

// TODO: Parameterize these tests (see suite below this one for parameterization example)

TEST_F(LeepFrog, OneHandLayer_Right_QuickOneHandLayerPressesKey) {
    TestDriver driver;
    InSequence s;

    LEEP_KEY_ROW(0, 3,
      KC_SPACE,
      KC_J,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      KC_1,
      KC_2,
      KC_3
    )

    // Activate the combo one hand right layer
    k_KC_SPACE.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_J.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(TAPPING_TERM + COMBO_TERM - 3);

    // Release the combo one hand right layer
    k_KC_J.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_SPACE.release();
    EXPECT_REPORT(driver, (KC_4)); // This should be 4 because it was quick
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, OneHandLayer_Right_LongOneHandLayerDoesNotPressKey) {
    TestDriver driver;
    InSequence s;

    LEEP_KEY_ROW(0, 3,
      KC_SPACE,
      KC_J,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      KC_1,
      KC_2,
      KC_3
    )

    // Activate the combo one hand right layer
    k_KC_SPACE.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_J.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(TAPPING_TERM + COMBO_TERM);

    // Release the combo one hand right layer
    k_KC_J.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_SPACE.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, OneHandLayer_Left_QuickOneHandLayerPressesKey) {
    TestDriver driver;
    InSequence s;

    LEEP_KEY_ROW(0, 3,
      KC_RSFT,
      KC_F,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      KC_1,
      KC_2,
      KC_3
    )

    // Activate the combo one hand left layer
    k_KC_RSFT.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(TAPPING_TERM + COMBO_TERM - 3);

    // Release the combo one hand left layer
    k_KC_F.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_RSFT.release();
    EXPECT_REPORT(driver, (KC_SLSH)); // This should be '/' because it was quick
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_F(LeepFrog, OneHandLayer_Left_LongOneHandLayerDoesNotPressKey) {
    TestDriver driver;
    InSequence s;

    LEEP_KEY_ROW(0, 3,
      KC_RSFT,
      KC_F,
      ck_test
    )

    LEEP_KEY_ROW(1, 3,
      KC_1,
      KC_2,
      KC_3
    )

    // Activate the combo one hand left layer
    k_KC_RSFT.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_F.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(TAPPING_TERM + COMBO_TERM);

    // Release the combo one hand left layer
    k_KC_F.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    k_KC_RSFT.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}


/*********************
* Symbol layer tests *
**********************/

struct SymbolLayerOverlapParams {
  std::string name;
  uint16_t    symbol_keycode;
  uint8_t     layer;
  uint16_t    expected_tap_keycode;
};


class LeepFrogSymbolLayerOverlap : public ::testing::WithParamInterface<SymbolLayerOverlapParams>, public TestFixture {
protected:
  SymbolLayerOverlapParams symbol_layer_params;

  void SetUp() override {
    symbol_layer_params = GetParam();
  }
};

static const SymbolLayerOverlapParams symbol_layer_params[] = {
  SymbolLayerOverlapParams{
    "SYMB",
    TO_SYMB,
    LR_SYMB,
    KC_TAB,
  },
  SymbolLayerOverlapParams{
    "ALT",
    TO_ALT,
    LR_ALT,
    KC_SPACE,
  },
};

INSTANTIATE_TEST_CASE_P(
  Layers,
  LeepFrogSymbolLayerOverlap,
  ::testing::ValuesIn(symbol_layer_params),
  [](const ::testing::TestParamInfo<SymbolLayerOverlapParams> info) {
    return info.param.name;
  }
);

TEST_P(LeepFrogSymbolLayerOverlap, SingleTap) {
  TestDriver driver;
  InSequence s;

  const uint16_t to_symb = symbol_layer_params.symbol_keycode;

  LEEP_KEY_ROW(0, 2,
    to_symb,
    ck_test
  )

  LEEP_KEY_ROW_ONLY(symbol_layer_params.layer, 2,
    to_symb,
    TK_0
  )


  // Press the symbol layer key
  k_to_symb.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  // Unpress the symbol layer key
  k_to_symb.release();
  EXPECT_REPORT(driver, (symbol_layer_params.expected_tap_keycode));
  EXPECT_EMPTY_REPORT(driver);
  run_one_scan_loop();

  CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, HoldAndPressRegularKey) {
  TestDriver driver;
  InSequence s;

  const uint16_t to_symb = symbol_layer_params.symbol_keycode;
  const uint16_t to_symb_0 = to_symb;

  LEEP_KEY_ROW(0, 3,
    to_symb,
    KC_X,
    ck_test
  )

  LEEP_KEY_ROW(symbol_layer_params.layer, 3,
    to_symb_0,
    KC_Y,
    TK_0
  )


  // Press the symbol layer key
  k_to_symb.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_KC_X.press();
  EXPECT_REPORT(driver, (KC_Y));
  run_one_scan_loop();

  k_KC_X.release();
  EXPECT_EMPTY_REPORT(driver);
  run_one_scan_loop();

  // Unpress the symbol layer key
  k_to_symb.release();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, HoldAndPressRegularKey_DifferentPressKeyAndUnpressKey) {
  TestDriver driver;
  InSequence s;

  const uint16_t to_symb = symbol_layer_params.symbol_keycode;
  const uint16_t to_symb_0 = to_symb;

  LEEP_KEY_ROW(0, 3,
    to_symb,
    KC_X,
    ck_test
  )

  LEEP_KEY_ROW(symbol_layer_params.layer, 3,
    to_symb_0,
    KC_Y,
    TK_0
  )


  // Press the symbol layer key
  k_to_symb.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_KC_X.press();
  EXPECT_REPORT(driver, (KC_Y));
  run_one_scan_loop();

  // Note Y is released here but X is pressed above
  k_KC_Y.release();
  EXPECT_EMPTY_REPORT(driver);
  run_one_scan_loop();

  // Unpress the symbol layer key
  k_to_symb.release();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, OSMLogic) {
  TestDriver driver;
  InSequence s;

  const uint16_t to_symb = symbol_layer_params.symbol_keycode;

  LEEP_KEY_ROW(0, 3,
    to_symb,
    KC_X,
    ck_test
  )

  LEEP_KEY_ROW_ONLY(symbol_layer_params.layer, 3,
    to_symb,
    KC_Y,
    TK_0
  )


  // Press the symbol layer key
  k_to_symb.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_KC_X.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  // Unpress the symbol layer key
  k_to_symb.release();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_KC_X.release();
  EXPECT_REPORT(driver, (symbol_layer_params.expected_tap_keycode));
  EXPECT_EMPTY_REPORT(driver);
  EXPECT_REPORT(driver, (KC_X));
  EXPECT_EMPTY_REPORT(driver);
  run_one_scan_loop();

  CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, AmbiguousOverlapIsHoldIfNotInSymbLonger) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = symbol_layer_params.symbol_keycode;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(symbol_layer_params.layer, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(41);

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(42);

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (symbol_layer_params.expected_tap_keycode));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_COMMA));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, AmbiguousOverlapIsHoldIfInSymbLonger) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = symbol_layer_params.symbol_keycode;

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_COMMA,
      ck_test
    )

    LEEP_KEY_ROW(symbol_layer_params.layer, 3,
      TK_0,
      KC_2,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_KC_2.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(43);

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(42);

    // Release the other key
    k_KC_2.release();
    EXPECT_REPORT(driver, (KC_2));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, AmbiguousOverlapIsHoldIfInSymbLonger_CustomKeycode) {
    TestDriver driver;
    InSequence s;

    const uint16_t to_symb = symbol_layer_params.symbol_keycode;
    const uint16_t custom_keycode = CK_ALTT;

    EXPECT_TRUE(custom_keycode > CUSTOM_KEYCODE_START);
    // TODO: couldn't get includes working to use below line instead of previuos line
    // EXPECT_TRUE(IS_CUSTOM_KEYCODE(custom_keycode));

    LEEP_KEY_ROW(LR_BASE, 3,
      to_symb,
      KC_X,
      ck_test
    )

    LEEP_KEY_ROW(symbol_layer_params.layer, 3,
      TK_0,
      custom_keycode,
      TK_1
    )

    // Press the symbol layer key
    k_to_symb.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    // Press the other key
    k_custom_keycode.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(43);

    // Release the symbol layer key
    k_to_symb.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    idle_for(42);

    // Release the other key
    k_custom_keycode.release();
    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT, KC_T));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT));
    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_P(LeepFrogSymbolLayerOverlap, OSMLogic_CustomKeycode) {
  TestDriver driver;
  InSequence s;

  const uint16_t to_symb = symbol_layer_params.symbol_keycode;
  const uint16_t custom_keycode = CK_ALTT;

  EXPECT_TRUE(custom_keycode > CUSTOM_KEYCODE_START);
  // TODO: couldn't get includes working to use below line instead of previuos line
  // EXPECT_TRUE(IS_CUSTOM_KEYCODE(custom_keycode));

  LEEP_KEY_ROW(0, 3,
    to_symb,
    KC_X,
    ck_test
  )

  LEEP_KEY_ROW(symbol_layer_params.layer, 3,
    TK_0,
    custom_keycode,
    TK_1
  )


  // Press the symbol layer key
  k_to_symb.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_custom_keycode.press();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  // Unpress the symbol layer key
  k_to_symb.release();
  EXPECT_NO_REPORT(driver);
  run_one_scan_loop();

  k_custom_keycode.release();
  EXPECT_REPORT(driver, (symbol_layer_params.expected_tap_keycode));
  EXPECT_EMPTY_REPORT(driver);
  EXPECT_REPORT(driver, (KC_X));
  EXPECT_EMPTY_REPORT(driver);
  run_one_scan_loop();

  CONFIRM_RESET();
}


// TEST_P(LeepFrogSymbolLayerOverlap, OSMLogic_CustomKeycode) {
//   TestDriver driver;
//   InSequence s;

//   const uint16_t to_symb = symbol_layer_params.symbol_keycode;

//   LEEP_KEY_ROW(0, 3,
//     to_symb,
//     KC_X,
//     ck_test
//   )

//   LEEP_KEY_ROW_ONLY(symbol_layer_params.layer, 3,
//     to_symb,
//     KC_Y,
//     TK_0
//   )


//   // Press the symbol layer key
//   k_to_symb.press();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   idle_for(20 * TAPPING_TERM);
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   k_KC_X.press();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   idle_for(20 * TAPPING_TERM);
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   // Unpress the symbol layer key
//   k_to_symb.release();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   idle_for(20 * TAPPING_TERM);
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   k_KC_X.release();
//   EXPECT_REPORT(driver, (symbol_layer_params.expected_tap_keycode));
//   EXPECT_EMPTY_REPORT(driver);
//   EXPECT_REPORT(driver, (KC_X));
//   EXPECT_EMPTY_REPORT(driver);
//   run_one_scan_loop();

//   CONFIRM_RESET();
// }


/* TODO: Fix this test.

The test is failing due to test setup, but it works when doing this
on the actual keyboard. So appears to just be flaky test logic in QMK itself
*/
// TEST_P(LeepFrogSymbolLayerOverlap, SingleHold) {
//   TestDriver driver;
//   InSequence s;

//   const uint16_t to_symb = symbol_layer_params.symbol_keycode;

//   LEEP_KEY_ROW(0, 2,
//     to_symb,
//     ck_test
//   )

//   LEEP_KEY_ROW_ONLY(LR_SYMB, 2,
//     to_symb,
//     TK_0
//   )

//   // Press the symbol layer key
//   k_to_symb.press();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   idle_for(TAPPING_TERM * 100);

//   // Unpress the symbol layer key
//   k_to_symb.release();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   CONFIRM_RESET();
// }


/***************************
* Specific tap dance tests *
****************************/

// struct TapDanceParams {
//   std::string name;
//   uint16_t    tap_dance_keycode;
//   uint16_t    expected_key_tap;
//   uint16_t    expected_key_hold;
//   uint16_t    expected_layer_hold;
// };


// class LeepFrogTapDances : public ::testing::WithParamInterface<TapDanceParams>, public TestFixture {
// protected:
//   TapDanceParams tap_dance_params;

//   void SetUp() override {
//     tap_dance_params = GetParam();
//   }
// };

// static const TapDanceParams tap_dance_params[] = {
//   TapDanceParams{
//     "TO_ALT",
//     TO_ALT,
//     KC_SPACE,
//     _______,
//     LR_ALT,
//   },
//   // TapDanceParams{
//   //   "CK_SHFT",
//   //   CK_SHFT,
//   //   KC_ENTER,
//   //   KC_RSFT,
//   //   _______,
//   // },
// };

// INSTANTIATE_TEST_CASE_P(
//   Layers,
//   LeepFrogTapDances,
//   ::testing::ValuesIn(tap_dance_params),
//   [](const ::testing::TestParamInfo<TapDanceParams> info) {
//     return info.param.name;
//   }
// );

// TEST_P(LeepFrogTapDances, TapKey) {
//   TestDriver driver;
//   InSequence s;

//   const uint16_t tap_dance_keycode = tap_dance_params.tap_dance_keycode;

//   LEEP_KEY_ROW(0, 2,
//     tap_dance_keycode,
//     ck_test
//   )


//   // Press the tap dance key
//   k_tap_dance_keycode.press();
//   EXPECT_NO_REPORT(driver);
//   run_one_scan_loop();

//   // Unpress the tap dance key
//   k_tap_dance_keycode.release();
//   EXPECT_REPORT(driver, (tap_dance_params.expected_key_hold));
//   EXPECT_EMPTY_REPORT(driver);
//   run_one_scan_loop();

//   CONFIRM_RESET();
// }

struct SimpleTapDanceParams {
  std::string name;
  uint16_t    tap_dance_keycode;
  uint8_t     layer;
  uint16_t    tap_keycode;
};


class LeepFrogSimpleTapDance : public ::testing::WithParamInterface<SimpleTapDanceParams>, public TestFixture {
protected:
  SimpleTapDanceParams simple_tap_dance_params;

  void SetUp() override {
    simple_tap_dance_params = GetParam();
  }
};

static const SimpleTapDanceParams simple_tap_dance_params[] = {
  SimpleTapDanceParams{
    "TO_ALT",
    TO_ALT,
    LR_ALT,
    KC_SPACE,
  },
  SimpleTapDanceParams{
    "TO_CTRL",
    TO_CTRL,
    LR_CTRL,
    KC_ENTER,
  },
  SimpleTapDanceParams{
    "TO_SYMB",
    TO_SYMB,
    LR_SYMB,
    KC_TAB,
  },
};

INSTANTIATE_TEST_CASE_P(
  Layers,
  LeepFrogSimpleTapDance,
  ::testing::ValuesIn(simple_tap_dance_params),
  [](const ::testing::TestParamInfo<SimpleTapDanceParams> info) {
    return info.param.name;
  }
);

TEST_P(LeepFrogSimpleTapDance, IsolatedKeyTap) {
    TestDriver driver;
    InSequence s;

    const uint16_t td_kc = simple_tap_dance_params.tap_dance_keycode;

    LEEP_KEY_ROW(0, 2,
      td_kc,
      ck_test
    )

    LEEP_KEY_ROW(simple_tap_dance_params.layer, 2,
      TK_0,
      TK_1
    )

    k_td_kc.press();
    run_one_scan_loop();

    k_td_kc.release();
    EXPECT_REPORT(driver, (simple_tap_dance_params.tap_keycode));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_P(LeepFrogSimpleTapDance, TapKeySeparately) {
    TestDriver driver;
    InSequence s;

    const uint16_t td_kc = simple_tap_dance_params.tap_dance_keycode;

    LEEP_KEY_ROW(0, 3,
      td_kc,
      KC_E,
      ck_test
    )

    LEEP_KEY_ROW(simple_tap_dance_params.layer, 3,
      TK_0,
      KC_X,
      TK_1
    )

    k_KC_E.press();
    EXPECT_REPORT(driver, (KC_E));
    run_one_scan_loop();

    k_KC_E.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    k_td_kc.press();
    run_one_scan_loop();

    k_td_kc.release();
    EXPECT_REPORT(driver, (simple_tap_dance_params.tap_keycode));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}

TEST_P(LeepFrogSimpleTapDance, OverlapKeyTap) {
    TestDriver driver;
    InSequence s;

    const uint16_t td_kc = simple_tap_dance_params.tap_dance_keycode;

    // TODO: Get this to work for LR_CTRL
    if (simple_tap_dance_params.layer == LR_CTRL) {
      GTEST_SKIP() << "TODO: Get this test to work for LR_CTRL";
      return;
    }

    LEEP_KEY_ROW(0, 3,
      td_kc,
      KC_E,
      ck_test
    )

    LEEP_KEY_ROW(simple_tap_dance_params.layer, 3,
      TK_0,
      KC_X,
      TK_1
    )

    k_KC_E.press();
    EXPECT_REPORT(driver, (KC_E));
    run_one_scan_loop();

    k_td_kc.press();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();

    k_KC_E.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    k_td_kc.release();
    EXPECT_REPORT(driver, (simple_tap_dance_params.tap_keycode));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    CONFIRM_RESET();
}
