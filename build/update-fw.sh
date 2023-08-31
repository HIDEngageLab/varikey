#!/bin/bash

# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program bin/composed_hid_device.elf verify reset exit"
