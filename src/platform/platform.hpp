/**
 * \file platform.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

#include "random.hpp"
#include "temperature_interface.hpp"

namespace platform
{
    struct Temperature : public pulp::TemperatureInterface
    {
        const float get_value(void) const;
        const uint16_t get_raw_value(void) const;
    };

    extern Temperature temperature;
    extern pulp::Random random_generator;
}