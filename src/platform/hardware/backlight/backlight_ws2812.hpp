/**
 * \file backlight_ws2812.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BACKLIGHT_WS2812_HPP__
#define __PLATFORM_BACKLIGHT_WS2812_HPP__

#include "backlight_color.hpp"
#include "component_interface.hpp"

namespace platform
{
    namespace hardware
    {
        namespace backlight
        {
            enum INDEX
            {
                FIRST,
                SECOND,
                THIRD
            };

            struct BacklightWs2812 : public pulp::ComponentInterface
            {
                virtual void initialize();
                virtual void shutdown();

                void set_backlight(const engine::backlight::Color &,
                                   const engine::backlight::Color &);
            };
        }
    }
}

#endif /* __PLATFORM_BACKLIGHT_WS2812_HPP__ */
