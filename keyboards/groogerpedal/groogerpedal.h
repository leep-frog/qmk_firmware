#pragma once

// These are defined in the schematic diagram here: https://store-usa.arduino.cc/products/arduino-leonardo-with-headers
// The value to use in QMK is the relevant PXX value without the 'P'
#define LEONARDO_A0 F7
#define LEONARDO_A1 F6
#define LEONARDO_A2 F5
#define LEONARDO_A3 F4
#define LEONARDO_A4 F1
#define LEONARDO_A5 F0

#define LEONARDO_D2 D1
#define LEONARDO_D4 D4

// Custom debounce logic is implemented so we use this custom debounce value
// (and set DEBOUNCE to 0 in config.h)
#define LEEP_DEBOUNCE 20

#define POWER_PIN_COUNT 2
#define INPUT_PIN_COUNT 5

typedef uint8_t direction_t;

/*
Imagine the cross section for the middle, left, and right beams from an ant's eye view
if the ant is standing at the heel beam and facing forward:

        (L,2)       (R,4)
          |           |
          |           |
          N-W    N    N-E
          |           |
(M,1)-----S-W----S----S-E----(M,1)
          |           |
          |           |
        (L,2)       (R,4)

Then, consider the buttons that we want to press:

M_tap: tap foot in the middle
R/L_hold: slide foot left or right to press a key
R/L_tap: tap foot on right or left

Finally, consider the cases in which each button should be activated:

M_tap:
  * S -> N -> S

R_tap:
  * SE -> NE -> SE
  * S -> N -> NE -> SE
  * SW -> NW -> N -> NE -> SE

R_hold:
  * S -> SE (oress)
  * SE -> [any] (unpress)

Additionally, consider each beam to be a binary bit:
M (aka S): 1
L (aka W): 2
R (aka E): 4

Therefore, the following mappings exist:

                  |  Beams Broken   |
Value | Direction |  L  |  M  |  R  |
-------+-----------+-----+-----+-----+
  0   |    N      |     |     |     |
  1   |    S      |     |  X  |     |
  2   |    NW     |  X  |     |     |
  3   |    SW     |  X  |  X  |     |
  4   |    NE     |     |     |  X  |
  5   |    SE     |     |  X  |  X  |
  6   |  Invalid  |  X  |     |  X  |
  7   |  Invalid  |  X  |  X  |  X  |

*/

#define MIDDLE_BEAM 1
#define LEFT_BEAM 2
#define RIGHT_BEAM 4
#define HEEL_BEAM 8
#define FRONT_BEAM 16

// Heel up directions
#define DIR_HEEL_UP_S (MIDDLE_BEAM)
#define DIR_HEEL_UP_SW (MIDDLE_BEAM + LEFT_BEAM)
#define DIR_HEEL_UP_SE (MIDDLE_BEAM + RIGHT_BEAM)

// Heel beam directions
#define DIR_N (HEEL_BEAM)
#define DIR_S (HEEL_BEAM + MIDDLE_BEAM)
#define DIR_NW (HEEL_BEAM + LEFT_BEAM)
#define DIR_SW (HEEL_BEAM + MIDDLE_BEAM + LEFT_BEAM)
#define DIR_NE (HEEL_BEAM + RIGHT_BEAM)
#define DIR_SE (HEEL_BEAM + MIDDLE_BEAM + RIGHT_BEAM)

// Front beam directions
#define DIR_FORWARD_HEEL_UP (FRONT_BEAM)
#define DIR_FORWARD (FRONT_BEAM + MIDDLE_BEAM)

#define DIR_END (1 << INPUT_PIN_COUNT)
