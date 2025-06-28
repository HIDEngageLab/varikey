/**
 * \file keymatrix_apd5585_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_chip_component.hpp"

namespace platform::hardware
{
    struct KeymatrixApd5585Varikey : public KeymatrixApd5585
    {
        static const unsigned int AD5585_I2C_ADDRESS = 0x30;
        static const unsigned int PICO_I2C_SDA = 4;
        static const unsigned int PICO_I2C_SCL = 5;
        static const unsigned int AD5585_RST = 14;
        static const unsigned int AD5585_INT = 15;
        static const unsigned int PICO_I2C_SPEED = (400 * 1000);

        static const unsigned int W = 128;
        static const unsigned int H = 32;
    };
}
