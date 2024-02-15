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
#include "keymatrix_adp5585_type.hpp"
#include "soc_type.hpp"
#include "usart.hpp"
#include "usb_device.hpp"

namespace platform
{
    namespace board
    {
        struct BoardKeypad : public pulp::ComponentInterface
        {
            virtual ~BoardKeypad() {}

            const defines::IDENTIFIER getIdentifier() const;

            virtual void initialize();
            virtual void shutdown();

            virtual void perform();

            hardware::Backlight backlight;
            hardware::Display display;
            hardware::Keymatrix keypad;
            hardware::UsbDevice usb;
            hardware::UartDevice uart;
            driver::SoC soc;
        };
    }
}

#endif // __PLATFORM_KEYPAD_BOARD_HPP__
