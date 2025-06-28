/**
 * \file engine_gpio.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_GPIO_HPP__
#define __ENGINE_GPIO_HPP__

#include "board_defines.hpp"

namespace engine
{
    namespace gpio
    {
		using IDENTIFIER = platform::board::IDENTIFIER;
		using DIRECTION = platform::board::DIRECTION;
		using VALUE = platform::board::VALUE;

        extern void set_direction(const IDENTIFIER, DIRECTION);
        extern const DIRECTION get_direction(const IDENTIFIER);
        extern void set_value(const IDENTIFIER, const bool);
        extern const VALUE get_value(const IDENTIFIER);
        extern void enable_event(const bool);
    }
}

#endif // __ENGINE_GPIO_HPP__
