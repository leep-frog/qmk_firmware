#pragma once

// Note: mouse_report.x/y values are int8_t

// *_scroll_speed_accumulator accumulates the mouse_report.y values. Every cumulative ACCUMULATION_SIZE units equates to
// a single incrementation of scroll_speed.
static int16_t horz_scroll_speed_accumulator = 0;
static int16_t vert_scroll_speed_accumulator = 0;
// TODO: Make conditional accumulation size (e.g. only 1 unit every 64, then 1 unit every 32, etc.}
#define ACCUMULATION_SIZE 64
static int16_t horz_scroll_speed = 0;
static int16_t vert_scroll_speed = 0;
static bool scroll_speed_activated = false;

const int16_t SCROLL_SLOWDOWN = 1 << 8;
#define INCREMENT_SCROLL_BY ((SCROLL_SLOWDOWN / 2) - 1) // See groogermouse.c for reasoning for this
static int16_t scroll_count = 0;

void activateScrollSpeed(bool activated) {
  horz_scroll_speed = 0;
  vert_scroll_speed = 0;
  scroll_speed_activated = activated;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (IsMoving()) {
    return Move(mouse_report);
  }

  if (scroll_speed_activated) {
    // Increment the scroll speed
    horz_scroll_speed_accumulator += mouse_report.x;
    vert_scroll_speed_accumulator -= mouse_report.y;
    horz_scroll_speed += (horz_scroll_speed_accumulator / ACCUMULATION_SIZE);
    vert_scroll_speed += (vert_scroll_speed_accumulator / ACCUMULATION_SIZE);
    horz_scroll_speed_accumulator = horz_scroll_speed_accumulator % ACCUMULATION_SIZE;
    vert_scroll_speed_accumulator = vert_scroll_speed_accumulator % ACCUMULATION_SIZE;

    // Clear the mouse movements
    mouse_report.x = 0;
    mouse_report.y = 0;

    int16_t pos_horz_scroll_speed = (horz_scroll_speed < 0) ? -horz_scroll_speed : horz_scroll_speed;
    int16_t pos_vert_scroll_speed = (vert_scroll_speed < 0) ? -vert_scroll_speed : vert_scroll_speed;

    bool horz = pos_horz_scroll_speed > pos_vert_scroll_speed;
    int16_t scroll_speed = horz ? horz_scroll_speed : vert_scroll_speed;

    // Scroll speed up is scroll_speed, so want to scroll every scroll_speed/SCROLL_SLOWDOWN
    scroll_count = (scroll_count + INCREMENT_SCROLL_BY) % SCROLL_SLOWDOWN;

    bool negative = scroll_speed < 0;
    int16_t pos_scroll_speed = negative ? -scroll_speed : scroll_speed;

    // Couldn't make SCROLL_SLOWDOWN any bigger so do an extra reductin here.
    pos_scroll_speed /= 2;

    // See groogermouse.c for explanation of this logic
    int16_t offset = (pos_scroll_speed / SCROLL_SLOWDOWN) + (scroll_count < (pos_scroll_speed % SCROLL_SLOWDOWN) ? 1 : 0);
    if (negative) {
      offset = -offset;
    }

    if (horz) {
      mouse_report.h = offset;
    } else {
      mouse_report.v = offset;
    }
  }

  return mouse_report;
}
