NKRO_ENABLE = yes

TAP_DANCE_ENABLE = yes
# This is enabled in the base rules.mk, but doesn't seem required, so we removed it to clear up memory.
EXTRAKEY_ENABLE = no
# This is enabled in the base rules.mk, but doesn't seem required (since it already uses POINTING_DEVICE_ENABLE)
# It was removed to clear up memory
MOUSEKEY_ENABLE = yes

# I tried combos for a while, but it didn't work well (clicking two mouse buttons at
# the same time was awkward and inconsistent).
# COMBO_ENABLE = yes
