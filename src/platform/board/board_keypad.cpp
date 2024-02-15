/**
 * \file board.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include "board_keypad.hpp"
#include "revision.h"

namespace platform
{
    namespace board
    {
        const defines::IDENTIFIER BoardKeypad::getIdentifier() const
        {
            return platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER);
        }

        void BoardKeypad::initialize()
        {
            soc.initialize();
            backlight.initialize();
            display.initialize();
            usb.initialize();
            uart.initialize();
            keypad.initialize();
        }

        void BoardKeypad::shutdown()
        {
            soc.shutdown();
            keypad.shutdown();
            uart.shutdown();
            usb.shutdown();
            display.shutdown();
            backlight.shutdown();
        }

        void BoardKeypad::perform()
        {
            usb.perform();
            uart.perform();
            keypad.perform();
            soc.perform();
        }
    }
}
