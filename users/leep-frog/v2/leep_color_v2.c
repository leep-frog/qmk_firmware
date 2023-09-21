
#include "./leep_record_v2.h"

bool played_startup_song = false;

void leep_change_color(uint16_t a, uint8_t b, uint8_t c, uint8_t mode, bool force) {
  #ifdef ENABLE_LEEP_COLOR
    if ((!recording && !shift_toggled && played_startup_song) || force) {
        rgb_matrix_sethsv_noeeprom(a, b, c);
        rgb_matrix_mode_noeeprom(mode);
    }
  #endif
}

bool PlayedStartupSong(void) {
  return played_startup_song;
}

void SetPlayedStartupSong(bool b) {
  played_startup_song = b;
}
