/**
 * \file rp2040_soc.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_RP2040_HPP__
#define __PLATFORM_SOC_RP2040_HPP__

#include <stdint.h>

#include "component_interface.hpp"
#include "rp2040_temperature.hpp"
#include "rp2040_ticker.hpp"
#include "rp2040_timestamp.hpp"
#include "rp2040_watchdog.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040 : public pulp::ComponentInterface
        {
            virtual ~RP2040() {}

            virtual void initialize();
            virtual void shutdown();

            void perform();

            void i2c_scan();

            RP2040Temperature temperature;
            RP2040Ticker ticker;
            RP2040Timestamp timestamp;
            RP2040Watchdog watchdog;
        };
    }
}

#endif // __PLATFORM_SOC_RP2040_HPP__
