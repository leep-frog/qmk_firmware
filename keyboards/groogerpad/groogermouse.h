
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

typedef void (*joystick_direction_handler_t) (uint8_t direction);

// TODO: __attribute__((weak))
extern joystick_direction_handler_t left_joystick_handler;
extern joystick_direction_handler_t right_joystick_handler;
// void (uint8_t direction);
// void right_joystick_handler(uint8_t direction);
