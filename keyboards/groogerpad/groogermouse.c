#include "groogermouse.h"

/**************
 * Interfaces *
 **************/

// Overridable function for enabling/disabling mouse and scrolling
__attribute__((weak)) bool joystick_mouse_enabled(void) { return true; }
__attribute__((weak)) bool joystick_scroll_enabled(void) { return true; }

// Functions for handling joystick direction changes
__attribute__((weak)) void left_joystick_handler(enum joystick_direction_t direction) { }
__attribute__((weak)) void right_joystick_handler(enum joystick_direction_t direction) { }

// Joystick directions
uint8_t left_joystick_direction = CENTER;
uint8_t right_joystick_direction = CENTER;

/************
 * Printing *
 ************/

const int intBufLen = 18;

void print_int(int32_t number) {
  char intBuf[intBufLen];
  int i = 0;
  if (number < 0) {
    intBuf[i] = '-';
    number = -number;
    i++;
  }
  // TODO: Reverse buffer afterwards
  bool possibly_zero = true;
  for (; possibly_zero || number > 0; i++) {
    possibly_zero = false;
    intBuf[i] = '0' + (number % 10);
    number /= 10;
  }
  intBuf[i+1] = 'X';
  intBuf[i+2] = '\n';
  intBuf[i+3] = '\0';
  send_string(intBuf);
}

/***************
 * Mouse Logic *
 ***************/

/* Mouse speed logic description

Mouse speed per cycle = controller_speed[0] * (max_virtual_speed / max_controller_speed[0]) * (throttle_multiplier_effect[1]) * (virtual_mouse_granularity_effect[2])
                       (^speed per cycle^)
                       ( ------------- ^virtual mouse speed per cycle^ ------------ )
                       ( ----------------- ^virtual mouse speed per cycle with throttle multiplier^ ----------------- )
                       ( -------------------------------------- ^actual mouse speed per cycle with throttle multiplier^ ------------------------------------- )

[0] We also need to account for drift deadzone. If we just ignore all numbers in the deadzone AND don't change
the equation, then we can have issues. Namely, if the deadzone is equivalent to 7 virtual speed incrementations, then
our movement speed STARTS at 8! (not factorial haha, just excalamation point).
To account for this, we need to normalize the controller_speed relative to the drift by decrementing controller_speed and max_controller_speed accordingly

[1] "throttle_multiplier_effect" is a bit tricky. We want no throttle to result in a 1x multiplier and full throttle
to result in a (max_throttle_multiplier) multiplier. The following is the way to achieve that:
throttle_effect = (actual_throttle * (throttle_multiplier - 1) / max_throttle) + 1
                = (actual_throttle * (throttle_multiplier - 1) + max_throttle) / max_throttle

[2] virtual_mouse_granularity_effect is a way for us to emulate more granular (and slower) speeds than the mouse report allows.
For example, let's say we want 5x the granularity (so a value of 15 in our virtual speed equals a 3 in actual speed,
a value of 7 virtual results in 1.4 actual). The way we do this is by tracking the cycle index (mod granularity)
and rounding up/down the proportional number of times to achieve the fraction we want.
virtual_mouse_granularity_effect = 1 / granularity_multiplier

================================ Full equation ================================

                        [                                       (           max_virtual_speed           )   ( actual_throttle * (throttle_multiplier - 1) + max_controller_throttle )             ]   (           1            )
Mouse speed per cycle = [ (controller_speed - drift_deadzone) * ( ------------------------------------- ) * ( --------------------------------------------------------------------- ) + cycle_idx ] * ( ---------------------- )
                        [                                       ( max_controller_speed - drift_deadzone )   (                     max_controller_throttle                           )             ]   ( granularity_multiplier )

===============================================================================

Note: the maximum value this can be is: (max_virtual_speed * throttle_multiplier / granularity_multiplier).
As long as that can fit in int8_t (i.e. less than 2^7), then we're fine.
*/

// Fixed
const int64_t max_controller_speed = 512;
const int64_t max_controller_throttle = 1024;

typedef struct {
  uint8_t drift_deadzone;
  // int32_t to match other types, but it gets squared so it should be less than 2^8
  int32_t direction_drift_deadzone;
  // Need a smaller type to ensure multiplication overflow doesn't happen later
  uint8_t max_virtual_speed; // Proportional to speed
  uint8_t throttle_multiplier;
  // Based on how cycles affect movements, this usually runs smoothest when this is a power of 2.
  uint8_t granularity_multiplier; // Inversely proportional to actual speed
  uint8_t cycle_incrementer;
  uint8_t cycle_idx;
} joystick_config_t;

/* To make mouse granular speed smoother, we increment by [ (granularity_multiplier - 1) / 2 ]
 * Consider the case with 8 granularity and virtual speed of 3. We would round up if mouse index is >= 5:
 *
 * Then we get the following with the different approaches (^ for round up, v for round down):
 * Increment by 1:                 01234567 (vvvvv^^^)
 * Increment by other (8-1)/2=3:   03614725 (vv^vv^v^)
 *
 * By forcing granularity_multiplier to be a power of 2, we ensure the cycle_incrementer always has the best result.
 */
#define GRANULARITY_MULTIPLIER(granularity) .granularity_multiplier = (1 << granularity), .cycle_incrementer = ((1 << granularity) - 1) / 2, .cycle_idx = 0

joystick_config_t mouse_config = {
  .drift_deadzone = 64,
  .direction_drift_deadzone = 400,
  .max_virtual_speed = 8,
  .throttle_multiplier = 8,
  GRANULARITY_MULTIPLIER(4),
};

joystick_config_t scroll_config = {
  .drift_deadzone = 64,
  .direction_drift_deadzone = 400,
  .max_virtual_speed = 4,
  .throttle_multiplier = 8,
  GRANULARITY_MULTIPLIER(6),
};

void joystick_mouse_speed_increment(uint8_t offset) {
  if (offset <= (255 - mouse_config.max_virtual_speed)) {
    mouse_config.max_virtual_speed += offset;
  }
}
void joystick_mouse_speed_decrement(uint8_t offset) {
  if (offset <= mouse_config.max_virtual_speed) {
    mouse_config.max_virtual_speed -= offset;
  }
}
void joystick_scroll_speed_increment(uint8_t offset) {
  if (offset <= (255 - scroll_config.max_virtual_speed)) {
    scroll_config.max_virtual_speed += offset;
  }
}
void joystick_scroll_speed_decrement(uint8_t offset) {
  if (offset <= scroll_config.max_virtual_speed) {
    scroll_config.max_virtual_speed -= offset;
  }
}

// Note the types for numbers that may be negative need to remain consistent, otherwise we get unexpected behavior
// e.g. 8bit negative three (10000011) becomes positive 131 in 16bit (0000000010000011)
int8_t get_joystick_speed(joystick_config_t *joystick_config, int32_t signed_controller_speed, int32_t signed_controller_throttle) {
  // Work in uint64_t until the end to avoid type casting issues in intermediate calculations.

  // Flip negative if necessary.
  bool negative = signed_controller_speed < 0;
  uint64_t controller_speed = signed_controller_speed;
  // This isn't expected to ever be negative.
  uint64_t controller_throttle = signed_controller_throttle;
  if (negative) {
    negative = true;
    controller_speed = -signed_controller_speed;
  }

  // Ignore movement if in drift deadzone
  if (controller_speed < joystick_config->drift_deadzone) {
    return 0;
  }

  // To get the best precision, we calculate the full numerator and denominator separately (since rounding many several smaller operations can cause us to lose many fraction results).
  uint64_t numer = (controller_speed - joystick_config->drift_deadzone) * joystick_config->max_virtual_speed * (controller_throttle * (joystick_config->throttle_multiplier - 1) + max_controller_throttle);
  uint64_t denom = (max_controller_speed - joystick_config->drift_deadzone) * max_controller_throttle;
  uint64_t res = ((numer / denom) + joystick_config->cycle_idx) / joystick_config->granularity_multiplier;

  // Revert back to the proper type and make negative if relevant.
  int8_t signedRes = (int8_t) res;
  if (negative) {
    return -signedRes;
  }
  return signedRes;
}

void update_joystick_config(joystick_config_t *joystick_config, uint8_t *joystick_direction, int32_t x, int32_t y, joystick_direction_handler_t handler) {
  joystick_config->cycle_idx += joystick_config->cycle_incrementer;
  joystick_config->cycle_idx %= joystick_config->granularity_multiplier;

  // Check if in the deadzone
  int32_t deadzone = joystick_config->direction_drift_deadzone;
  uint8_t new_direction = CENTER;
  if (x*x + y*y > deadzone*deadzone) {
    // sin(22.5) = 0.38268
    int32_t numer =  383;
    int32_t denom = 1000;

    // Split circle by four lines:
    // y = +-0.38268*x     = +- x*(38268/100000)
    // y = +-(1/0.38268)*x = +- x*(100000/38268)
    // line# is true if y is above the line.
    bool line1 = y > (x*numer)/denom;
    bool line2 = y > -(x*numer)/denom;
    bool line3 = y > (x*denom)/numer;
    bool line4 = y > -(x*denom)/numer;

    // North and south are inverted (-y means joystick is pointing up)
    // Therefore, we flip all N/S occurrences
    if (line1 && !line2) {
      new_direction = WEST;
    } else if (!line1 && line2) {
      new_direction = EAST;
    } else if (line1 && !line3) {
      new_direction = SOUTHEAST;
    } else if (!line1 && line3) {
      new_direction = NORTHWEST;
    } else if (line3 && line4) {
      new_direction = SOUTH;
    } else if (!line3 && !line4) {
      new_direction = NORTH;
    } else if (line2 && !line4) {
      new_direction = SOUTHWEST;
    } else {
      new_direction = NORTHEAST;
    }
  }

  if (*joystick_direction != new_direction) {
    *joystick_direction = new_direction;
    handler(new_direction);
  };
}

bool pointing_device_task(void) {
  report_mouse_t report = pointing_device_get_report();

  update_joystick_config(&mouse_config, &left_joystick_direction, gamepad.axis_x, gamepad.axis_y, left_joystick_handler);
  if (joystick_mouse_enabled()) {
    report.x = get_joystick_speed(&mouse_config, gamepad.axis_x, gamepad.throttle);
    report.y = get_joystick_speed(&mouse_config, gamepad.axis_y, gamepad.throttle);
  }

  update_joystick_config(&scroll_config, &right_joystick_direction, gamepad.axis_rx, gamepad.axis_ry, right_joystick_handler);
  if (joystick_scroll_enabled()) {
    report.h = get_joystick_speed(&scroll_config, gamepad.axis_rx, gamepad.throttle);
    report.v = -get_joystick_speed(&scroll_config, gamepad.axis_ry, gamepad.throttle);
  }

  pointing_device_set_report(report);
  return pointing_device_send();
}
