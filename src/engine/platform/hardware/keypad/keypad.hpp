/**
 * \file keypad.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYPAD_HPP__
#define __PLATFORM_KEYPAD_HPP__

#include "keypad_apd5585_gossenmetrawatt.hpp"
#include "keypad_apd5585_varikey.hpp"
#include "platform_defines.hpp"
#include "revision.h"

namespace platform
{
    namespace hardware
    {
        namespace keypad
        {
            template <platform::defines::Value>
            struct Entity
            {
                using Type = platform::Undefined;
            };

            template <>
            struct Entity<platform::defines::Value::VARIKEY_1_0>
            {
                using Type = platform::hardware::KeypadApd5585Varikey;
            };
            template <>
            struct Entity<platform::defines::Value::GOSSENMETRAWATT_1_0>
            {
                using Type = platform::hardware::KeypadApd5585Gossenmetrawatt;
            };
        }
        using Keypad = keypad::Entity<platform::defines::Value(HARDWARE_IDENTIFIER)>::Type;
    }
}

#endif /* __PLATFORM_KEYPAD_HPP__ */
