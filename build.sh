#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

project_path=`pwd`

# define hardware paltform with
# available platforms are...
hw_plarform=VARIKEY
#hw_plarform=GOSSENMETRAWATT

# define product variant
# available products are...
#fw_product=KEYPAD_10BWDB
fw_product=KEYPAD_DEMO

cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-g++ -DHARDWARE_PLATFORM:STRING=${hw_plarform} -DFIRMWARE_PRODUCT:STRING=${fw_product} -S${project_path} -B${project_path}/bin -G "Unix Makefiles"
cmake --build ${project_path}/bin --config Debug --target all -j 6 --


