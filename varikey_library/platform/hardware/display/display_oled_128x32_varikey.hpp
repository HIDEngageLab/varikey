// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware display oled 128x32 varikey functionality
// SPDX-FileType: SOURCE

#pragma once

#include "display_oled_128x32.hpp"

namespace platform::hardware
{
    struct DisplayOLED128x32Varikey : public DisplayOLED128x32
    {
        static const unsigned int PICO_SPI_CS = 17;
        static const unsigned int PICO_SPI_SCK = 18;
        static const unsigned int PICO_SPI_TX = 19;
        static const unsigned int DISPLAY_RESET = 20;
        static const unsigned int DISPLAY_CMD_SEL = 21;
        static const unsigned int PICO_SPI_SPEED = (10 * 1000 * 1000);

        static const unsigned int W = 128;
        static const unsigned int H = 32;

        static const unsigned int C = 128;
        static const unsigned int R = 4;

        static const unsigned int MAX_LINE_LENGTH = 18;
    };
}
