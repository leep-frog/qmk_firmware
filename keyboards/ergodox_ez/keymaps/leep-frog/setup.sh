#!/bin/bash

if [[ ! $(grep "^source .*/keymaps/leep-frog/main.sh$" ~/.bashrc) ]]
then
  dir_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
  main_path="$dir_path/main.sh"

  echo Adding "source $main_path" to bashrc
  source $main_path
  echo "source $main_path" >> ~/.bashrc
fi
