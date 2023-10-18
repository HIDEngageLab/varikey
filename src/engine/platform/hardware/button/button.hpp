/**
 * \file button.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BUTTON_HPP__
#define __PLATFORM_BUTTON_HPP__

#include "button_mini_switch.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace button
        {
            template <platform::defines::Value>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Value::VARIKEY_1_0>
            {
                using Type = platform::hardware::button::MiniSwitch;
            };
            template <>
            struct Entity<platform::defines::Value::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::button::MiniSwitch;
            };
        }

        using Button = button::Entity<platform::defines::Value(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_BUTTON_HPP__ */
