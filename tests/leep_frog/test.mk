# Copyright 2022 Jouke Witteveen
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# --------------------------------------------------------------------------------
# Keep this file, even if it is empty, as a marker that this folder contains tests
# --------------------------------------------------------------------------------

TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

# INTROSPECTION_KEYMAP_C = ../../../users/leep-frog/main.c
INTROSPECTION_KEYMAP_C = leep_keyboard.c

# SRC += leep_keyboard.c
SRC += ../../../users/leep-frog/v2/leep_index_v2.c
# SRC += ../../../users/leep-frog/keyboard-main/leep_index_kb.c

# SRC += ../../../users/leep-frog/main.c
