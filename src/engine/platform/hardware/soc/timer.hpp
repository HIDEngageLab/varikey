/**
 * \file timer.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_TIMER_HPP__
#define __PLATFORM_TIMER_HPP__

#include "platform_defines.hpp"
#include "timer_rp2040.hpp"

namespace platform
{
    namespace driver
    {
        namespace timer
        {
            template <platform::defines::Value>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Value::VARIKEY_1_0>
            {
                using Type = platform::driver::TimerRP2040;
            };
            template <>
            struct Entity<platform::defines::Value::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::driver::TimerRP2040;
            };
        }
        using Timer = timer::Entity<platform::defines::Value(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* PLATFORM_TIMER_H_ */
