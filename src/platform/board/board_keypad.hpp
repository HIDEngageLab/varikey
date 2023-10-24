/**
 * \file board.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BOARD_KEYPAD_HPP__
#define __PLATFORM_BOARD_KEYPAD_HPP__

#include "component_interface.hpp"
#include "platform_defines.hpp"

#include "backlight_type.hpp"
#include "display_type.hpp"
#include "keypad_type.hpp"
#include "soc_type.hpp"
#include "usb_device.hpp"

namespace platform
{
    namespace board
    {
        struct BoardKeypad : public pulp::ComponentInterface
        {
            virtual ~BoardKeypad() {}

            const defines::Identifier getIdentifier() const;

            virtual void initialize();
            virtual void shutdown();

            virtual void perform();

            hardware::Backlight backlight;
            hardware::Display display;
            hardware::Keypad keypad;
            hardware::UsbDevice usb;
            driver::SoC soc;
        };
    }
}

#endif // __PLATFORM_KEYPAD_BOARD_HPP__
