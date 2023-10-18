/**
 * \file backlight_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BACKLIGHT_VARIKEY_H__
#define __PLATFORM_BACKLIGHT_VARIKEY_H__

namespace platform
{
    namespace hardware
    {
        struct BacklightVarikey
        {
            static const unsigned int BACKLIGHT_PIN = 22;
        };
    }
}

#endif /* __PLATFORM_BACKLIGHT_VARIKEY_H__ */
