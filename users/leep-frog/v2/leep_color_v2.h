#pragma once

bool PlayedStartupSong(void);
void SetPlayedStartupSong(bool b);
void LeepUnlock(bool play_music);

#ifdef ENABLE_LEEP_COLOR

extern int layer_colors[][3];

void leep_change_color(uint16_t a, uint8_t b, uint8_t c, uint8_t mode, bool force);
void leep_change_mode(uint8_t mode, bool force);

// Stock HSV_ORANGE (21, 255, 255) reads as yellow on these keyboards' RGB
// LEDs, which render green more strongly than the raw HSV math assumes.
// Shifting the hue closer to red compensates for that.
#    define HSV_LEEP_ORANGE 4, 255, 255

// Stock HSV_YELLOW (43, 255, 255) reads as green-ish for the same reason --
// the green channel renders stronger than requested, so pull the hue back
// toward orange to compensate.
#    define HSV_LEEP_YELLOW 24, 255, 255

// Stock HSV_GOLD (36, 255, 255) reads as near-white for the same reason --
// the green channel renders stronger than requested, so pull the hue back
// toward orange and drop the value a bit so it reads as gold, not a pale
// yellow-white.
#    define HSV_LEEP_GOLD 26, 255, 220

// Stock HSV_TURQUOISE (123, 90, 112) is quite dim and washed out. Push
// saturation and value up so it actually reads as a bright turquoise.
#    define HSV_LEEP_TURQUOISE 123, 200, 255

// Stock HSV_PINK (234, 128, 255) is only half-saturated, which combined with
// these LEDs' tendency to wash colors out reads as white. Push saturation up
// so it actually reads as pink.
#    define HSV_LEEP_PINK 234, 220, 255

// This macro is incase we ever switch from hsv representation to rgb or vice versa.
#    define LEEP_C(clr) HSV_##clr
#    define LEEP_LAYER_COLOR(lyr, force) leep_change_color(layer_colors[lyr][0], layer_colors[lyr][1], layer_colors[lyr][2], RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_SOLID_COLOR(clr, force) leep_change_color(LEEP_C(clr), RGB_MATRIX_SOLID_COLOR, force);
#    define LEEP_COLOR_MODE(clr, mde, force) leep_change_color(LEEP_C(clr), mde, force);
#    define LEEP_MODE_ONLY(mde, force) leep_change_mode(mde, force)

#else // ifdef ENABLE_LEEP_COLOR

#    define LEEP_C(clr) 0
#    define LEEP_LAYER_COLOR(lyr, force)
#    define LEEP_SOLID_COLOR(clr, force)
#    define LEEP_COLOR_MODE(clr, mde, force)
#    define LEEP_MODE_ONLY(mde, force)

#endif // ifdef ENABLE_LEEP_COLOR
