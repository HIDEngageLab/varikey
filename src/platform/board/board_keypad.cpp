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
        const defines::Identifier BoardKeypad::getIdentifier() const
        {
            return platform::defines::Identifier(HARDWARE_IDENTIFIER);
        }

        void BoardKeypad::initialize()
        {
            soc.initialize();
            backlight.initialize();
            display.initialize();
            usb.initialize();
            keypad.initialize();
        }

        void BoardKeypad::shutdown()
        {
            soc.shutdown();
            keypad.shutdown();
            usb.shutdown();
            display.shutdown();
            backlight.shutdown();
        }

        void BoardKeypad::perform()
        {
            usb.perform();
            keypad.perform();
            soc.perform();
        }
    }
}
