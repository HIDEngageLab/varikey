/**
 * \file display_oled_128x32.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DISPLAY_OLED_128X32_HPP__
#define __PLATFORM_DISPLAY_OLED_128X32_HPP__

#include "component_interface.hpp"

namespace platform
{
    namespace hardware
    {
        struct DisplayOLED128x32 : public pulp::ComponentInterface
        {
            virtual void initialize();
            virtual void shutdown();
        };
    }
}

#endif /* __PLATFORM_DISPLAY_OLED_128X32_HPP__ */
