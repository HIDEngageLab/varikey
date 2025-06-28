/**
 * \file rp2040_watchdog.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_SOC_RP2040_WATCHDOG_HPP__
#define __PLATFORM_SOC_RP2040_WATCHDOG_HPP__

#include "component_interface.hpp"

namespace platform
{
    namespace soc
    {
        struct RP2040Watchdog : public pulp::ComponentInterface
        {
            virtual ~RP2040Watchdog() {}

            virtual void initialize() {}
            virtual void shutdown() {}

            void start();
            void update();
            void reboot();
        };
    }
}

#endif