#!/bin/bash

# Installing QMK was done by following the instructions here:
# https://beta.docs.qmk.fm/tutorial/newbs_getting_started#windows
# pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
# May need to restart terminal after the previous command finishes for this work
# python3 -m pip install qmk

# Setup QMK using this directory.
qmk setup leep-frog/qmk_firmware

# Add main.sh sourcing to bash profile
if [[ ! $(grep "^source .*/keymaps/leep-frog/main.sh$" ~/.bashrc) ]]
then
  dir_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
  main_path="$dir_path/main.sh"

  echo Adding "source $main_path" to bashrc
  source $main_path
  echo "source $main_path" >> ~/.bashrc
fi
