/**
 * \file keypad_backlight_command.hpp
 * \author Roman Koch (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_KEYPAD_BACKLIGHT_MODE_HPP__
#define __ENGINE_KEYPAD_BACKLIGHT_MODE_HPP__

#include <stdint.h>

namespace engine
{
    namespace keypad
    {
        namespace backlight
        {
            enum class COMMAND : uint8_t
            {
                PROGRAM_MEDIUM = 0x01,
                PROGRAM_SLOW = 0x02,
                PROGRAM_TURBO = 0x03,
                CONST = 0x04,
                NOT_MOUNTED = 0x05,
                MOUNTED = 0x06,
                SUSPENDED = 0x07,
                OFF = 0x08,
                MORPH = 0xaa,
                SET = 0xab,
            };
        }
    }
}

#endif // __ENGINE_KEYPAD_BACKLIGHT_MODE_HPP__
