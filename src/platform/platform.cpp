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

    extern void initialize(void)
    {
        board::assembly.initialize();
    }

    extern void shutdown(void)
    {
        board::assembly.shutdown();
    }

    extern void reboot(void)
    {
        board::assembly.reboot();
    }

    extern void bootsel(void)
    {
        board::assembly.bootsel();
    }

    const float Temperature::get_value(void) const
    {
        return board::assembly.soc.get_temperature();
    }

    const uint16_t Temperature::get_raw_value(void) const
    {
        return board::assembly.soc.get_temperature_raw();
    }
} // namespace platform
