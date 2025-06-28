/**
 * \file backlight_mode.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_BACKLIGHT_MODE_HPP__
#define __ENGINE_BACKLIGHT_MODE_HPP__

#include <stdint.h>

namespace engine
{
    namespace backlight
    {
        enum class PROGRAM : uint8_t
        {
            ALERT = 0x00,
            CONST = 0x01,
            MEDIUM = 0x02,
            MORPH = 0x03,
            MOUNT = 0x04,
            OFF = 0x05,
            SET = 0x06,
            SLOW = 0x07,
            SUSPEND = 0x08,
            TURBO = 0x09,
            UNDEFINED = 0xff,
        };
    }
}

#endif
