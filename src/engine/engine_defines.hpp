/**
 * \file engine_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DEFINES_HPP__
#define __ENGINE_DEFINES_HPP__

namespace engine
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class Identifier
        {
            KEYPAD_DEMO = 1,
            KEYPAD_10BWDB = 2,
        };
    }
}

#endif // __ENGINE_DEFINES_HPP__
