#pragma once

#define LEEP_SLOW_DOWN 3
#define MOVE_WINDOWS 6
#define MOVE_WINDOW_MS 500

const uint8_t MOVES[MOVE_WINDOWS][2] = {
  {1, 0},
  {0, 0},
  {0, -1},
  {-1, 0},
  {0, 0},
  {0, 1},
};

static bool leep_moving = false;
static uint16_t move_timer = 0;

void ToggleMove(void) {
  leep_moving = !leep_moving;
  if (leep_moving) {
    move_timer = timer_read();
  }
}

bool IsMoving(void) {
  return leep_moving;
}

report_mouse_t Move(report_mouse_t mouse_report) {
  // To avoid issues when the timer overlaps the start time.
  uint16_t now = timer_read();
  uint16_t elapsed = timer_elapsed(move_timer);
  if ((now != move_timer) && (elapsed % (MOVE_WINDOWS * MOVE_WINDOW_MS)) == 0) {
    move_timer = now;
  }

  if ((elapsed % LEEP_SLOW_DOWN) != 0) {
    return mouse_report;
  }

  // Move the mouse
  uint16_t move_idx = (timer_elapsed(move_timer) % (MOVE_WINDOWS * MOVE_WINDOW_MS)) / MOVE_WINDOW_MS;
  mouse_report.x = MOVES[move_idx][0];
  mouse_report.y = MOVES[move_idx][1];
  return mouse_report;
}
