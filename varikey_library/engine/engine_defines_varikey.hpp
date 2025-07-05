// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Varikey-specific engine definitions
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "display_font.hpp"
#include "display_image.hpp"

namespace engine::defines
{
    struct Varikey
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
