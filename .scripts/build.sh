#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

pushd ..
workspace=$(pwd)

if ! command -v cmake >/dev/null 2>&1; then
    echo "cmake could not be found"
    exit
fi

# clean up

#rm -f ${workspace}/bin/CMakeCache.txt
#rm -Rf ${workspace}/bin/CMakeFiles

# configure

# define hardware platform with
#hw_plarform=VARIKEY
#hw_plarform=GOSSENMETRAWATT

# define product variant
#fw_product=KEYPAD_10BWDB
#fw_product=KEYPAD_DEMO

#-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc \
#-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-g++ \
#-DHARDWARE_PLATFORM:STRING=${hw_plarform} \
#-DFIRMWARE_PRODUCT:STRING=${fw_product} \

cmake --no-warn-unused-cli \
    -DCMAKE_BUILD_TYPE:STRING=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
    -S${workspace} \
    -B${workspace}/bin \
    -G "Unix Makefiles"

# clean
cmake --build ${workspace}/bin --config Debug --target clean -j 6

# build all
cmake --build ${workspace}/bin --config Debug --target all -j 6 --

popd
