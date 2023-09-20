# This file intentionally left blank
CUSTOM_MATRIX = lite
SEND_STRING_ENABLE = yes
QUANTUM_LIB_SRC += uart.c
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
SRC += matrix.c
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
#DYNAMIC_MACRO_ENABLE = yes

# From: https://docs.qmk.fm/#/squeezing_avr
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
