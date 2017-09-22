#!/bin/sh

script_dir="`cd $(dirname $0); pwd`"

$script_dir/../run.sh -c icg -i icg-image -r "-w=/home/user/work" "$@"
