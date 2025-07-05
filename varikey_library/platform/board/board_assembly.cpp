// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Board assembly implementation
// SPDX-FileType: SOURCE

#include <stdio.h>

#include "board_assembly.hpp"
#include "revision.h"

namespace platform::board
{
    platform::board::Assembly assembly;

    const defines::IDENTIFIER Assembly::getIdentifier() const
    {
        return platform::defines::IDENTIFIER(identity::hardware::IDENTIFIER);
    }

    void Assembly::initialize()
    {
        soc.initialize();
        backlight.initialize();
        // display.initialize();
        usb.initialize();
        uart.initialize();
        keypad.initialize();
    }

    void Assembly::shutdown()
    {
        keypad.shutdown();
        uart.shutdown();
        usb.shutdown();
        // display.shutdown();
        backlight.shutdown();
        soc.shutdown();
    }

    void Assembly::perform()
    {
        usb.perform();
        uart.perform();
        keypad.perform();
        soc.perform();
    }
}
