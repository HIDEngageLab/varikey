/**
 * \file engine_defines_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

#include "display_font.hpp"
#include "display_image.hpp"

namespace engine
{
    namespace defines
    {
        struct Varikey15SBLA
        {
            static const bool ENABLE_SERAIL_INTERFACE_ON_START = true;
            static const bool ENABLE_USB_INTERFACE_ON_START = true;

            static constexpr const char *INTRO = "VARIKEY";
            static const display::ICON LOGO = display::ICON::VARIKEY_LOGO;
            static const display::FONT FONT_SIZE = display::FONT::NORMAL;
            static const int8_t INTRO_ROW = 2;
            static const int8_t INTRO_COL = 30;
        };
    }
}
