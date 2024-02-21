/**
 * \file parameter_identifier.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace registry
{
    namespace parameter
    {
        /**
            \brief Parameter identifier type
        */
        enum class IDENTIFIER : uint8_t
        {
            BACKLIGHT = 0xA1,
            DISPLAY = 0xA3,
            FEATURES = 0x51,
            KEYPAD = 0xA2,
            MAINTAINER = 0x23,
            MAPPING = 0xB0,
            POSITION = 0x24,
            SERIAL_NUMBER = 0x11,
            USER = 0x70,

            UNDEFINED = 0xff,
        };

        extern const IDENTIFIER to_identifier(const uint8_t);
    }
}
