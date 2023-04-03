#ifndef LEEP_COLOR
#define LEEP_COLOR

bool recording           = false;
bool shift_toggled       = false;
bool played_startup_song = false;

#define ENABLE_LEEP_COLOR

#ifdef ENABLE_LEEP_COLOR

void leep_change_color(uint16_t a, uint8_t b, uint8_t c, uint8_t mode, bool force) {
    if ((!recording && !shift_toggled && played_startup_song) || force) {
        rgb_matrix_sethsv_noeeprom(a, b, c);
        rgb_matrix_mode_noeeprom(mode);
    }
}

// This macro is incase we ever switch from hsv representation to rgb or vice versa.
#    define LEEP_C(clr) HSV_##clr
#    define LEEP_LAYER_COLOR(lyr, force) leep_change_color(layer_colors[lyr][0], layer_colors[lyr][1], layer_colors[lyr][2], RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_SOLID_COLOR(clr, force) leep_change_color(LEEP_C(clr), RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_COLOR_MODE(clr, mde, force) leep_change_color(LEEP_C(clr), mde, force);

int layer_colors[NUM_LAYERS][3] = {
    [0 ... NUM_LAYERS - 1] =
        {//
         LEEP_C(GREEN)},
    // Base layer
    [LR_BASE] = {LEEP_C(CYAN)},
    // Safe layer
    [LR_SAFE] = {LEEP_C(GREEN)},
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
};

#else  // ifdef ENABLE_LEEP_COLOR

#    define LEEP_LAYER_COLOR(lyr, force)
#    define LEEP_SOLID_COLOR(clr, force)
#    define LEEP_COLOR_MODE(clr, mde, force)

#endif  // ifdef ENABLE_LEEP_COLOR

#endif  // ifndef LEEP_COLOR
