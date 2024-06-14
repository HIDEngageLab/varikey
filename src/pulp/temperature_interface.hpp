/**
 * \file board_interface.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    struct TemperatureInterface
    {
        virtual const float get_value(void) const = 0;
        virtual const uint16_t get_raw_value(void) const = 0;
    };
}