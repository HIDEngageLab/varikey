#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

# check parameter
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <value1> <value2>"
    exit 1
fi

current_path=`pwd`

group=$1
identifier=$2

pass_phrase="__UNIT_TEST_DONE__"
log_filename=serial_output.txt

printf '%04x%04x', $group $identifier | sed 's/\(..\)\(..\)/\2\1/g' | xxd -r -p > parameters.bin 
${current_path}/picotool/bin/picotool load -v parameters.bin -o 0x20002000
rm -f parameters.bin

# set port params and redirect test output
stty -F /dev/ttyUSB0 115200 cs8 -cstopb -parenb  
cat /dev/ttyUSB0 >> ${log_filename} & 
cat_pid=$!

# reboot in app mode (= start app. don't worry: test app reboot in bootsel mode)
${current_path}/picotool/bin/picotool reboot -a

# check for a pass prase to kill this script
tail -f ${log_filename} | while read LINE; do
  echo "$LINE"
  if [[ "$LINE" == *${pass_phrase}* ]]; then
    kill -SIGINT $cat_pid
    break
  fi
done

sleep 0.75
kill $cat_pid
