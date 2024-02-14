/**
 * \file payload_identifier.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_PAYLOAD_IDENTIFIER_HPP__
#define __ENGINE_PAYLOAD_IDENTIFIER_HPP__

#include <cstdint>
#include <type_traits>

namespace engine
{
    namespace payload
    {
        enum class IDENTIFIER : uint8_t
        {
            BACKLIGHT = 0x10,
            DISPLAY = 0x30,
            GADGET = 0x40,
            GPIO = 0x50,
            IDENTITY = 0xA0,
            KEYCODE = 0x65,
            KEYPAD = 0x70,
            PARAMETER = 0xB0,
            RESET = 0xEE,
            TEMPERATURE = 0xC0,
            UNDEFINED = 0xFF,
        };

        constexpr int operator+(IDENTIFIER _report, int _value)
        {
            return static_cast<int>(_report) + _value;
        }

        template <typename E>
        constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept
        {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }

    }
}

#endif // __ENGINE_PAYLOAD_IDENTIFIER_HPP__
