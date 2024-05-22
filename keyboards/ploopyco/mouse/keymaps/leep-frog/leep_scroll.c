#pragma once

static int16_t scroll_speed = 0;
static bool scroll_speed_activated = false;

const int16_t SCROLL_SLOWDOWN = 1 << 8;
#define INCREMENT_SCROLL_BY ((SCROLL_SLOWDOWN / 2) - 1) // See groogermouse.c for reasoning for this
static int16_t scroll_count = 0;

void activateScrollSpeed(bool activated) {
  scroll_speed = 0;
  scroll_speed_activated = activated;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  scroll_speed += clockwise ? 1 : -1;
  return !scroll_speed_activated;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (IsMoving()) {
    return Move(mouse_report);
  }

  if (scroll_speed_activated) {
    // Scroll speed up is scroll_speed, so want to scroll every scroll_speed/SCROLL_SLOWDOWN
    scroll_count = (scroll_count + INCREMENT_SCROLL_BY) % SCROLL_SLOWDOWN;

    bool negative = scroll_speed < 0;
    int16_t pos_scroll_speed = negative ? -scroll_speed : scroll_speed;

    // See groogermouse.c for explanation of this logic
    int16_t offset = (pos_scroll_speed / SCROLL_SLOWDOWN) + (scroll_count < (pos_scroll_speed % SCROLL_SLOWDOWN) ? 1 : 0);
    if (negative) {
      offset = -offset;
    }

    if (transpose_scrolling()) {
      mouse_report.h = offset;
    } else {
      mouse_report.v = offset;
    }
  }

  return mouse_report;
}
