#include "leep_music_v2.h"

static bool _leep_mute = false;
bool IsMuted(void) { return _leep_mute; }

#ifdef AUDIO_ENABLE
static bool _mute_just_colored = false;
#endif

static void mute_sound(bool pressed, bool with_sound) {
    #ifdef AUDIO_ENABLE
    if (!pressed) {
        return;
    }

    _mute_just_colored = true;
    if (_leep_mute) {
        if (with_sound) {
            // Play the full song before muting
            SNG_UNMUTE();
        }
        _leep_mute = false;
        LEEP_SOLID_COLOR(GREEN, false);
        if (!with_sound) {
            // Play the short tune after muting
            SNG_UNMUTE();
        }
    } else {
        if (with_sound) {
            // Play the short tune before unmuting
            SNG_MUTE();
        }
        LEEP_SOLID_COLOR(ORANGE, false);
        _leep_mute = true;
        if (with_sound) {
            // Play the full song after unmuting
            SNG_MUTE();
        }
    }
    #endif
}

void Mute_handled(keyrecord_t* record) {
  #ifdef AUDIO_ENABLE
    // Unpressing mute key
    if (!record->event.pressed) {
        return;
    }

    if (_mute_just_colored) {
        LEEP_LAYER_COLOR(LR_BASE, false);
        _mute_just_colored = false;
    }
    #endif
}

void LeepMute(void) { _leep_mute = true; }

void MuteWithoutSound(bool pressed) { mute_sound(pressed, false); }

void MuteWithSound(bool pressed) { mute_sound(pressed, true); }
