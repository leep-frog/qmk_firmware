#include "./leep_music_v2.h"
#include "./leep_color_v2.h"

// Explicitly only define each song once (not once per use) to limit memory usage.
// All song uses should exclusively be used through references to these
// existing songs (and not by creating new song instances).
DEFINE_SONG(zelda_discover, SONG(ZELDA_DISCOVERY));
// DEFINE_SONG(zelda_guardian_battle_song, SONG(ZELDA_GUARDIAN_BATTLE));
DEFINE_SONG(zelda_item_found, SONG(ZELDA_ITEM_FOUND));
DEFINE_SONG(zelda_spirit_orb, SONG(ZELDA_SPIRIT_ORB));

DEFINE_SONG(leep_start, SONG(LEEP_START_SNG));
DEFINE_SONG(leep_end, SONG(LEEP_END_SNG));

DEFINE_SONG(mario_1_up, SONG(MARIO_1_UP));
DEFINE_SONG(mario_lost_a_life, SONG(MARIO_LOST_A_LIFE));
DEFINE_SONG(mario_game_over, SONG(MARIO_GAME_OVER));

DEFINE_SONG(mario_uw_1, SONG(MARIO_UNDERWORLD_1));
DEFINE_SONG(mario_uw_2, SONG(MARIO_UNDERWORLD_2));

DEFINE_SONG(leep_dud, SONG(LEEP_DUD));

DEFINE_SONG(leep_silence, SONG());
DEFINE_SONG(leep_success, SONG(LEEP_SUCCESS));

// We define our own start-up song (instead of using STARTUP_SONG)
// so we can add logic that disables the custom startup song.
void SNG_STARTUP(void) { LEEP_PLAY_SONG(zelda_discover, leep_silence); }
void SNG_RESET(void) { LEEP_PLAY_SONG(mario_game_over, leep_dud); }
void SNG_MUTE(void) { LEEP_PLAY_SONG(mario_lost_a_life, leep_silence); }
void SNG_UNMUTE(void) { LEEP_PLAY_SONG(mario_1_up, leep_silence); }
void SNG_REC_START(void) { LEEP_PLAY_SONG(leep_start, leep_start); }
void SNG_REC_1_END(void) { LEEP_PLAY_SONG(zelda_item_found, leep_end); }
void SNG_REC_2_END(void) { LEEP_PLAY_SONG(mario_1_up, leep_end); }
void SNG_REC_1_PLAY(void) { LEEP_PLAY_SONG(zelda_spirit_orb, leep_success); }
void SNG_REC_2_PLAY(void) { LEEP_PLAY_SONG(zelda_discover, leep_success); }
void SNG_EYE_START(void) { LEEP_PLAY_SONG(mario_uw_1, leep_success); }
void SNG_EYE_END(void) { LEEP_PLAY_SONG(mario_uw_2, leep_success); }
void SNG_COPY(void) { LEEP_PLAY_SONG(leep_start, leep_start); }
void SNG_PASTE(void) { LEEP_PLAY_SONG(leep_end, leep_end); }
void SNG_DUD(void) { LEEP_PLAY_SONG(leep_dud, leep_dud); }


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
        LEEP_LAYER_COLOR(0, false);
        _mute_just_colored = false;
    }
    #endif
}

void LeepMute(void) { _leep_mute = true; }

void MuteWithoutSound(bool pressed) { mute_sound(pressed, false); }

void MuteWithSound(bool pressed) { mute_sound(pressed, true); }
