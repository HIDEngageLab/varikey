/**
 * \file engine_defines_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DEFINES_GOSSENMETRAWATT_HPP__
#define __ENGINE_DEFINES_GOSSENMETRAWATT_HPP__

#include <cstdint>

#include "display_image.hpp"

namespace engine
{
    namespace defines
    {
        struct Gossenmetrawatt
        {
            static const bool ENABLE_SERAIL_INTERFACE_ON_START = true;
            static const bool ENABLE_USB_INTERFACE_ON_START = true;

            static constexpr const char *INTRO = "GMCI";
            static const display::ICON LOGO = display::ICON::GOSSENMETRAWATT_LOGO;
            static const display::FONT FONT_SIZE = display::FONT::BIG;
            static const int8_t INTRO_ROW = 1;
            static const int8_t INTRO_COL = 30;
        };
    }
}

#endif // __ENGINE_DEFINES_GOSSENMETRAWATT_HPP__
