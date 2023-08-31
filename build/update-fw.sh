#!/bin/bash
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg  -c "program bin/composed_hid_device.elf verify reset exit"

