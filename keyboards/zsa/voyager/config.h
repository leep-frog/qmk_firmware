// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_COLS 7
#define MATRIX_ROWS 12

#define MCP23018_TIMEOUT 10

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_VCC

#define IS31FL3731_I2C_TIMEOUT 5

// #define MOUSEKEY_WHEEL_INTERVAL MOUSEKEY_INTERVAL
// #define MOUSEKEY_WHEEL_MAX_SPEED MOUSEKEY_MAX_SPEED
// #define MOUSEKEY_WHEEL_TIME_TO_MAX MOUSEKEY_TIME_TO_MAX


// #define WEBUSB_LANDING_PAGE_URL u8"configure.ergodox-ez.com"
// #define EEPROM_I2C_24LC128

/* COL2ROW or ROW2COL */
// #define DIODE_DIRECTION ROW2COL

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

#define MOUSEKEY_INTERVAL           20
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          7
#define MOUSEKEY_WHEEL_DELAY        400
#define MOUSEKEY_WHEEL_INTERVAL     MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED    MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX  MOUSEKEY_TIME_TO_MAX

// #define FIRMWARE_VERSION_SIZE 17
// #define DYNAMIC_KEYMAP_EEPROM_ADDR (EECONFIG_SIZE + FIRMWARE_VERSION_SIZE)


// #define MUSIC_MAP

// #define AUDIO_PIN A5
// #define AUDIO_PIN_ALT A4
// #define AUDIO_PIN_ALT_AS_NEGATIVE
