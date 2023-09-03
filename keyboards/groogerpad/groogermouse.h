
#pragma once

enum joystick_direction_t {
  CENTER = 0,
  WEST,
  NORTHWEST,
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
};

extern uint8_t left_joystick_direction;
extern uint8_t right_joystick_direction;

typedef void (joystick_direction_handler_t) (enum joystick_direction_t);

bool joystick_mouse_enabled(void);
bool joystick_scroll_enabled(void);

extern joystick_direction_handler_t left_joystick_handler;
extern joystick_direction_handler_t right_joystick_handler;
