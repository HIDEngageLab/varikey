// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload identifier module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <type_traits>

namespace engine::payload
{
    enum class IDENTIFIER : uint8_t
    {
        BACKLIGHT = 0x01,
        DISPLAY = 0x02,
        GADGET = 0x03,
        GPIO = 0x04,
        HASH = 0x05,
        IDENTITY = 0x06,
        KEYPAD = 0x07,
        PARAMETER = 0x08,
        PROTOCOL = 0x09,
        RESET = 0x0A,
        TEMPERATURE = 0x0B,

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
