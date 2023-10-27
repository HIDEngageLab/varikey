/**
 * \file keypad_display_command.hpp
 * \author Roman Koch (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_DISPLAY_COMMAND_HPP__
#define __ENGINE_KEYPAD_DISPLAY_COMMAND_HPP__

#include <stdint.h>

namespace engine
{
    namespace keypad
    {
        namespace display
        {
            enum class FONT : uint8_t
            {
                SMALL = 0x01, /* default */
                NORMAL = 0x02,
                BIG = 0x03,
                HUGE = 0x04,
                SYMBOL = 0x05,
            };
        }
    }
}

#endif // __ENGINE_KEYPAD_DISPLAY_COMMAND_HPP__