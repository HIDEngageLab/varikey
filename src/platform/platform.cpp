/**
 * \file platform.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "platform.hpp"
#include "board_assembly.hpp"

namespace platform
{
    Temperature temperature;
    pulp::Random random_generator(temperature);

    const float Temperature::get_value(void) const
    {
        return platform::board::assembly.soc.get_temperature();
    }
    const uint16_t Temperature::get_raw_value(void) const
    {
        return platform::board::assembly.soc.get_temperature_raw();
    }
} // namespace platform
