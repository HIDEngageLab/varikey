/**
 * \file temperature_rp2040.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "temperature_rp2040.hpp"

namespace platform
{
    namespace driver
    {
        const int TemperatureRP2040::get() const { return 500; }
    }
}
