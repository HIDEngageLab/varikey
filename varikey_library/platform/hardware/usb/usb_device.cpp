// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware usb device functionality
// SPDX-FileType: SOURCE

#include "bsp/board.h"
#include "tusb.h"

#include "usb_device.hpp"

namespace platform::hardware
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