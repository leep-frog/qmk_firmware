#pragma once

#define LEEP_SLOW_DOWN 3
#define MOVE_KEYS 6
#define MOVE_WINDOW_MS 500

const static uint8_t MOVES[MOVE_KEYS] = {
  QK_MOUSE_CURSOR_RIGHT,
  KC_NO,
  QK_MOUSE_CURSOR_DOWN,
  QK_MOUSE_CURSOR_LEFT,
  KC_NO,
  QK_MOUSE_CURSOR_UP,
};

static bool leep_moving = false;

void LeepMouse_ToggleMove(void) {
  leep_moving = !leep_moving;
  if (leep_moving) {
    tap_code16(KC_S);
  } else {
    tap_code16(KC_E);
  }
}

void LeepMouse_Move(void) {
  if (!leep_moving) {
    return;
  }

  uint16_t cur_time = timer_read();

  if ((cur_time % LEEP_SLOW_DOWN) != 0) {
    return;
  }

  // Move the mouse
  uint8_t move_idx = (cur_time % (MOVE_KEYS * MOVE_WINDOW_MS)) / MOVE_WINDOW_MS;
  uint8_t move_key = MOVES[move_idx];
  tap_code16(move_key);
}

bool LeepMouse_Handler(keyrecord_t *record, custom_keycode_value_t *_) {
  if (!record->event.pressed) {
    LeepMouse_ToggleMove();
  }
  return false;
}

bool LeepMouse_StopMoving(void) {
  bool ret_val = leep_moving;
  leep_moving = false;
  return ret_val;
}
