
#include "./leep_record_v2.h"

bool played_startup_song = false;

void leep_change_color(uint16_t a, uint8_t b, uint8_t c, uint8_t mode, bool force) {
    if ((!recording && !shift_toggled && played_startup_song) || force) {
        rgb_matrix_sethsv_noeeprom(a, b, c);
        rgb_matrix_mode_noeeprom(mode);
    }
}

/*int layer_colors[NUM_LAYERS][3] = {
    [0 ... NUM_LAYERS - 1] =
        {//
         LEEP_C(GREEN)},
    // Base layer
    [LR_BASE] = {LEEP_C(CYAN)},
    // Ella layer
    [LR_ELLA] = {LEEP_C(GREEN)},
    // Ctrl layer
    [LR_CTRL] = {LEEP_C(SPRINGGREEN)},
    // Alt layer
    [LR_ALT] = {LEEP_C(MAGENTA)},
    // Ctrl+X layer
    [LR_CTRL_X] = {LEEP_C(CHARTREUSE)},
    // Ctrl+Alt layer
    [LR_CTRL_ALT] = {LEEP_C(GOLD)},
    // Nav layer
    [LR_NAVIGATION] = {LEEP_C(CORAL)},
    // Shortcut layer
    [LR_SHORTCUTS] = {LEEP_C(TURQUOISE)},
    // Symbol layer
    [LR_SYMB] = {LEEP_C(ORANGE)},
    // Outlook layer
    [LR_OUTLOOK] = {LEEP_C(BLUE)},
    // Scroll layer
    [LR_SCROLL] = {LEEP_C(RED)},
};*/
