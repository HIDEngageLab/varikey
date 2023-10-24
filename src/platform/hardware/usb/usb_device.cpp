/**
 * \file usb_device.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "bsp/board.h"
#include "tusb.h"

#include "usb_device.hpp"

namespace platform
{
    namespace hardware
    {
        void UsbDevice::initialize()
        {
            board_init();
            tusb_init();
            while (!tusb_inited())
                ;
        }

        void UsbDevice::shutdown()
        {
        }

        void UsbDevice::perform()
        {
            tud_task();
        }
    }
}