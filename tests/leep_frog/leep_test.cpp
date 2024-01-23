#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"
#include "leep_keyboard.h"
// #include "../../../../users/leep-frog/main.c"

using testing::_;
using testing::InSequence;

class LeepFrog : public TestFixture {};

TEST_F(LeepFrog, Basic) {
    TestDriver driver;
    InSequence s;
    auto       key_rls = KeymapKey(0, 1, 0, KC_A);

    set_keymap({key_rls});

    /* Single press and unpress */
    key_rls.press();
    EXPECT_REPORT(driver, (KC_A));
    run_one_scan_loop();

    key_rls.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
}
