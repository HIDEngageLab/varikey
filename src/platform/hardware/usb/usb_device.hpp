/**
 * \file usb_device.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_USB_DEVICE_HPP__
#define __PLATFORM_USB_DEVICE_HPP__

#include "component_interface.hpp"

namespace platform
{
    namespace hardware
    {
        struct UsbDevice : public pulp::ComponentInterface
        {
            virtual void initialize();
            virtual void shutdown();

            void perform();
        };
    }
}

#endif // __PLATFORM_USB_DEVICE_HPP__
