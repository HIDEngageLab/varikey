/**
 * \file display_oled_128x32_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 * 
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_DISPLAY_OLED_128X32_GOSSENMETRAWATT_H__
#define __PLATFORM_DISPLAY_OLED_128X32_GOSSENMETRAWATT_H__

namespace platform
{
    namespace hardware
    {
        struct DisplayOLED128x32Gossenmetrawatt
        {
            static const unsigned int DISPLAY_CMD_SEL = 21;
            static const unsigned int DISPLAY_RESET = 20;
            static const unsigned int PICO_SPI_CS = 17;
            static const unsigned int PICO_SPI_SCK = 18;
            static const unsigned int PICO_SPI_TX = 19;
            static const unsigned int PICO_SPI_SPEED = (10 * 1000 * 1000);

            static const unsigned int W = 128;
            static const unsigned int H = 32;
        };
    }
}

#endif /* __PLATFORM_DISPLAY_OLED_128X32_GOSSENMETRAWATT_H__ */
