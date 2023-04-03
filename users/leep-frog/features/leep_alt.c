// Alt+tab functions

static bool leep_toggling_alt = false;

#define ALT_DOWN() SEND_STRING(SS_DOWN(X_RALT))
#define ALT_UP() SEND_STRING(SS_UP(X_RALT))

bool AltTab_handled(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return false;
    }

    bool td_alt_key_pressed = (keycode == CK_ATB) || (keycode == CK_SATB);
    // End alt layer if any key other than alt togglers.
    if (leep_toggling_alt && !td_alt_key_pressed) {
        leep_toggling_alt = false;
        ALT_UP();
        return true;
    }
    return false;
}

void AltTab_deactivate(bool activated) {
    if (!activated) {
        leep_toggling_alt = false;
        ALT_UP();
    }
}

void AltTab_run(bool pressed) {
    if (pressed) {
        leep_toggling_alt = true;
        ALT_DOWN();
        SEND_STRING(SS_TAP(X_TAB));
    }
}

void AltTab_runShift(bool pressed) {
    if (pressed) {
        leep_toggling_alt = true;
        ALT_DOWN();
        SEND_STRING(SS_RSFT(SS_TAP(X_TAB)));
    }
}

#undef START_ALT
#undef END_ALT
