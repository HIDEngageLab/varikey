/**
 * \file display_position.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DISPLAY_POSITION_HPP__
#define __ENGINE_DISPLAY_POSITION_HPP__

#include <cstdint>

namespace engine
{
    namespace display
    {
        struct Position
        {
            uint8_t line;
            uint8_t column;
        };
    }
}

#endif /* __ENGINE_DISPLAY_POSITION_HPP__ */
