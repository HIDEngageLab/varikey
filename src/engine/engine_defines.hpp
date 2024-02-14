/**
 * \file engine_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DEFINES_HPP__
#define __ENGINE_DEFINES_HPP__

#include <cstdint>

namespace engine
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class Identifier
        {
            KEYPAD_DEMO = 1,   /* varikey demonstrator board */
            KEYPAD_10BWDB = 2, /* 10 buttons, 1 wheel, display, backlight */
        };

        enum class STATE : uint8_t
        {
            ACTIVE = 0x01,
            IDLE = 0x00,
            PENDING = 0x03,
            SUSPEND = 0x02,
            UNDEFINED = 0xff,
        };
    }

}

#endif // __ENGINE_DEFINES_HPP__
