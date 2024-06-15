#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

# --------------------------------------------------
# update ubuntu
# --------------------------------------------------

#sudo apt update
#sudo apt upgrade -y
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake

pushd ..

root_path=`pwd`

pushd ..

# --------------------------------------------------
# download picotool sources
# --------------------------------------------------

if [ -d "picotool" ]; then
	cd picotool
	git reset --hard
	git pull
	rm -f build/CMakeCache.txt
else
	git clone https://github.com/raspberrypi/picotool.git 
	cd picotool
fi

if [ ! -d "build" ]; then
	mkdir build
fi

# --------------------------------------------------
# build & install picotool
# --------------------------------------------------

export PICO_SDK_PATH=${root_path}/bin/_deps/pico_sdk-src/

cd build
cmake -DCMAKE_INSTALL_PREFIX=${root_path}/tools/picotool -G "Unix Makefiles" ..
make install

sudo cp build/udev/99-picotool.rules /etc/udev/rules.d/

popd
popd
