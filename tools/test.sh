#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

# check parameter
if [ "$#" -eq 2 ]; then
    group=$1
    identifier=$2
    binary_file=""
elif [ "$#" -eq 3 ]; then
    group=$1
    identifier=$2
    binary_file=$3
else
    echo "Usage: $0 <group> <identifier> [binary.uf2]"
    exit 1
fi

current_path=$(pwd)
picotool_path=${current_path}/picotool/bin

usb_device=/dev/ttyUSB0

pass_phrase="__UNIT_TEST_DONE__"
log_filename=serial_output.txt
param_filename=parameter.bin
backup_filename=parameter-backup.bin

flash_address=0x10100000
flash_address1=0x10100002

# create binary file with parameter values (note: little endian!)
echo "group:      ${group}" 
echo "identifier: ${identifier}" 
echo "binary:     ${binary_file}" 

if [[ -n "$binary_file" ]]; then
    ${picotool_path}/picotool load -u -v ${binary_file}
    ${picotool_path}/picotool reboot -a
    sleep 1
fi

echo "param filename: ${current_path}/${param_filename}"
printf '%04x%04x', $group $identifier | sed 's/\(..\)\(..\)/\2\1/g' | xxd -r -p > ${param_filename} 
# optional: save backup
# ${picotool_path}/picotool save -r ${flash_address} ${flash_address1} ${backup_filename}
# upload parameter in pico flash
${picotool_path}/picotool load -u -v ${param_filename} -o ${flash_address}
# clean up
rm -f ${param_filename}

# set port params and redirect test output
stty -F ${usb_device} 115200 cs8 -cstopb -parenb  
cat ${usb_device} >> ${log_filename} & 
cat_pid=$!

# reboot in app mode (= start app. don't worry: test app reboot in bootsel mode)
${picotool_path}/picotool reboot -a

# check for a pass prase to kill this script
tail -f ${log_filename} | while read LINE; do
  echo "$LINE"
  if [[ "$LINE" == *${pass_phrase}* ]]; then
    kill -SIGINT $cat_pid
    break
  fi
done

# check if pico back from reboot
#sleep 0.75
for i in {1..200}
do
    sleep 0.1
    ${picotool_path}/picotool info > /dev/null      
    if [ $? -eq 0 ]; then
        break
    fi
done

kill $cat_pid
rm -f ${log_filename}
