// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_audio.md#songs

#ifdef TEMPO_DEFAULT
#    undef TEMPO_DEFAULT
#endif
#define TEMPO_DEFAULT 180

// https://www.ninsheetmusic.org/download/pdf/3544
#define ZELDA_ITEM_FOUND FE_7(H__NOTE, _FS6, _AS6, _CS7, _B6, _DS7, _FS7, _CS8),
#define ZELDA_DISCOVERY FE_8(H__NOTE, _G7, _F7, _DS7, _A6, _GS6, _E7, _GS7, _C8),
#define ZELDA_SPIRIT_ORB /* Intro arpeggion */ FE_7(E__NOTE, _A5, _B5, _CS6, _D6, _E6, _FS6, _GS6), /* mid part */ W__NOTE(_A6), H__NOTE(_REST), Q__NOTE(_A6), Q__NOTE(_REST), H__NOTE(_A6), H__NOTE(_G6), BD_NOTE(_A6), /* Outro arpeggio // FE_9(E__NOTE, _E5, _A5, _CS6, _E6, _A6, _E7, _A7, _B7, _E8), */
#define ZELDA_GUARDIAN_BATTLE FE_12(QD_NOTE, _B7, _REST, _A6, _B6, _FS7, _AS6, _E7, _C7, _A7, _A6, _FS7, _B6), FE_12(QD_NOTE, _B7, _AS6, _FS7, _C7, _E7, _A6, _A7, _B6, _A6, _B6, _C7, _B7),

#define LEEP_START_SNG FE_2(H__NOTE, _C5, _G5)
#define LEEP_END_SNG FE_2(H__NOTE, _G5, _C6)

#define MARIO_1_UP FE_6(H__NOTE, _E6, _G6, _E7, _C7, _D7, _G7),
#define MARIO_GAME_OVER WD_NOTE(_C6), HD_NOTE(_REST), WD_NOTE(_G5), HD_NOTE(_REST), WD_NOTE(_E5), W__NOTE(_A5), W__NOTE(_B5), W__NOTE(_A5), W__NOTE(_AF5), W__NOTE(_BF5), W__NOTE(_AF5), BD_NOTE(_G5)
#define MARIO_LOST_A_LIFE HD_NOTE(_B5), W__NOTE(_F6), H__NOTE(_REST), H__NOTE(_F6), Q__NOTE(_REST), W__NOTE(_F6), W__NOTE(_E6), W__NOTE(_D6), HD_NOTE(_C6), H__NOTE(_E5), W__NOTE(_REST), HD_NOTE(_E5), HD_NOTE(_C5),
#define MARIO_KART_START FE_4(BD_NOTE, _G5, _G5, _G5, _G6)
#define MARIO_UNDERWORLD_1 FE_6(HD_NOTE, _C5, _C6, _A4, _A5, _AS4, _AS5)
#define MARIO_UNDERWORLD_2 FE_6(HD_NOTE, _F4, _F5, _D4, _D5, _DS4, _DS5)

#define LEEP_DUD FE_1(Q__NOTE, _C4)
#define LEEP_SUCCESS FE_1(Q__NOTE, _C6)

// other built-ins:
// MUSIC_ON_SOUND
// MUSIC_OFF_SOUND
// STARTUP_SOUND
// GOODBYE_SOUND
// QWERTY_SOUND

// From below link:
// https://github.com/qmk/qmk_firmware/pull/5905/files
#define ZELDA_PUZZLE Q__NOTE(_G5), Q__NOTE(_FS5), Q__NOTE(_DS5), Q__NOTE(_A4), Q__NOTE(_GS4), Q__NOTE(_E5), Q__NOTE(_GS5), HD_NOTE(_C6),

#define ZELDA_TREASURE Q__NOTE(_A4), Q__NOTE(_AS4), Q__NOTE(_B4), HD_NOTE(_C5),

#define MARIO_THEME Q__NOTE(_E5), H__NOTE(_E5), H__NOTE(_E5), Q__NOTE(_C5), H__NOTE(_E5), W__NOTE(_G5), Q__NOTE(_G4),

#define MARIO_GAMEOVER HD_NOTE(_C5), HD_NOTE(_G4), H__NOTE(_E4), H__NOTE(_A4), H__NOTE(_B4), H__NOTE(_A4), H__NOTE(_AF4), H__NOTE(_BF4), H__NOTE(_AF4), WD_NOTE(_G4),

// TODO: jeopardy theme?
// https://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0187869&gclid=CjwKCAjwmJeYBhAwEiwAXlg0AbKzu-nPgLqTuS_--k1zGnUbn9Vdkge5mHRX4xSVRFq19Sh-MZ-V1BoCNkQQAvD_BwE
