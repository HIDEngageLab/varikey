// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix type gmci functionality
// SPDX-FileType: SOURCE

#pragma once

#include "keymatrix_chip_component.hpp"

namespace platform::hardware
{
    struct KeymatrixApd5585Gmc : public KeymatrixApd5585
    {
        static const unsigned int AD5585_I2C_ADDRESS = 0x34;
        static const unsigned int PICO_I2C_SDA = 12;
        static const unsigned int PICO_I2C_SCL = 13;
        static const unsigned int AD5585_RST = 14;
        static const unsigned int AD5585_INT = 11;
        static const unsigned int PICO_I2C_SPEED = (400 * 1000);

        static const unsigned int W = 128;
        static const unsigned int H = 32;
    };
}
