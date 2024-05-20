
#pragma once

// Order of chars is center, then clockwise starting from west.
// (Note: changing this requires changing the word ordering in keymap.c)
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
  NUM_JOYSTICK_DIRECTIONS,
};

extern uint8_t left_joystick_direction;
extern uint8_t right_joystick_direction;

typedef void (joystick_direction_handler_t) (enum joystick_direction_t);

bool joystick_mouse_enabled(void);
bool joystick_scroll_enabled(void);

extern joystick_direction_handler_t left_joystick_handler;
extern joystick_direction_handler_t right_joystick_handler;

void joystick_mouse_speed_increment(uint8_t offset);
void joystick_mouse_speed_decrement(uint8_t offset);
void joystick_scroll_speed_increment(uint8_t offset);
void joystick_scroll_speed_decrement(uint8_t offset);
