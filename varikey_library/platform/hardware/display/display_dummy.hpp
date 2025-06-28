/**
 * \file display_oled_128x32_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"

namespace platform
{
    namespace hardware
    {
        struct DisplayDummy : public pulp::ComponentInterface
        {
            static const unsigned int PICO_SPI_CS = 5;
            static const unsigned int PICO_SPI_SCK = 5;
            static const unsigned int PICO_SPI_TX = 5;
            static const unsigned int DISPLAY_RESET = 5;
            static const unsigned int DISPLAY_CMD_SEL = 5;
            static const unsigned int PICO_SPI_SPEED = (10 * 1000 * 1000);

            static const unsigned int W = 128;
            static const unsigned int H = 32;

            static const unsigned int C = 128;
            static const unsigned int R = 4;

            static const unsigned int MAX_LINE_LENGTH = 18;

            virtual void initialize() {}
            virtual void shutdown() {}
            void symbol(uint8_t const line_start, uint8_t const line_end,
                        uint8_t const column_start, uint8_t const column_end,
                        uint8_t const *const data, size_t const len) {}
            void clean() {}
            void set_invert() {}
            void set_normal() {}
        };
    }
}
