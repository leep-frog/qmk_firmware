#!/bin/bash

export QMK_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
alias q="cd $QMK_PATH"

alias qc="qmk compile"
