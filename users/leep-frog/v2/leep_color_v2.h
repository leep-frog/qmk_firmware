#pragma once

extern int layer_colors[][3];

// TODO: Move to config file
#define ENABLE_LEEP_COLOR

#ifdef ENABLE_LEEP_COLOR

void leep_change_color(uint16_t a, uint8_t b, uint8_t c, uint8_t mode, bool force);

// This macro is incase we ever switch from hsv representation to rgb or vice versa.
#    define LEEP_C(clr) HSV_##clr
#    define LEEP_LAYER_COLOR(lyr, force) leep_change_color(layer_colors[lyr][0], layer_colors[lyr][1], layer_colors[lyr][2], RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_SOLID_COLOR(clr, force) leep_change_color(LEEP_C(clr), RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_COLOR_MODE(clr, mde, force) leep_change_color(LEEP_C(clr), mde, force);

#else // ifdef ENABLE_LEEP_COLOR

#    define LEEP_LAYER_COLOR(lyr, force)
#    define LEEP_SOLID_COLOR(clr, force)
#    define LEEP_COLOR_MODE(clr, mde, force)

#endif // ifdef ENABLE_LEEP_COLOR
