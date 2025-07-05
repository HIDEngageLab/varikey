// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: GMCI-specific engine definitions
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "display_image.hpp"

namespace engine::defines
{
    struct Gmci
    {
        static const bool ENABLE_SERAIL_INTERFACE_ON_START = true;
        static const bool ENABLE_USB_INTERFACE_ON_START = true;

        static constexpr const char *INTRO = "GMCI";
        static const display::ICON LOGO = display::ICON::GMCI_LOGO;
        static const display::FONT FONT_SIZE = display::FONT::BIG;
        static const int8_t INTRO_ROW = 1;
        static const int8_t INTRO_COL = 30;
    };
}
