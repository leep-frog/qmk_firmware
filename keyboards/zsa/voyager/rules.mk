# MCU_LDSCRIPT = voyager

# CUSTOM_MATRIX = lite
# PROGRAM_CMD = $(call EXEC_DFU)
# DFU_ARGS = -d 3297:0791 -a 0 -s 0x08002000:leave
# DFU_SUFFIX_ARGS = -v 3297 -p 0791

VPATH += drivers/gpio
SRC += matrix.c mcp23018.c
# I2C_DRIVER_REQUIRED = yes

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
# AUDIO_ENABLE = yes          # Audio output
# AUDIO_DRIVER = dac_additive
CUSTOM_MATRIX = lite
SWAP_HANDS_ENABLE = yes
RGB_MATRIX_ENABLE = yes

#project specific files
SRC += matrix.c
I2C_DRIVER_REQUIRED = yes

MOUSE_SHARED_EP = no
