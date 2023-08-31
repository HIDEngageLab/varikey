#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

if ! command -v openocd >/dev/null 2>&1; then
    echo "openocd could not be found"
    exit
fi

openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program bin/varikey.elf verify reset exit"
