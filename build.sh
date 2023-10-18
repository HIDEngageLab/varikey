#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

project_path=`pwd`

# define hardware paltform with
# available platforms are 
#hw_plarform=VARIKEY_1_0
hw_plarform=GOSSENMETRAWATT_1_0

cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-g++ -DHARDWARE_PLATFORM:STRING=${hw_plarform} -S${project_path} -B${project_path}/bin -G "Unix Makefiles"
cmake --build ${project_path}/bin --config Debug --target all -j 6 --
