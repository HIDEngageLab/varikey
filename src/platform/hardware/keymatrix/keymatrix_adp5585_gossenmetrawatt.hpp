/**
 * \file keymatrix_apd5585_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_APD5585_GOSSENMETRAWATT_HPP__
#define __PLATFORM_KEYMATRIX_APD5585_GOSSENMETRAWATT_HPP__

#include "keymatrix_adp5585.hpp"

namespace platform
{
    namespace hardware
    {
        struct KeymatrixApd5585Gossenmetrawatt : public KeymatrixApd5585
        {
            static const unsigned int AD5585_I2C_ADDRESS = 0x30;
            static const unsigned int PICO_I2C_SDA = 12;
            static const unsigned int PICO_I2C_SCL = 13;
            static const unsigned int AD5585_RST = 14;
            static const unsigned int AD5585_INT = 11;
            static const unsigned int PICO_I2C_SPEED = (100 * 1000);

            static const unsigned int W = 128;
            static const unsigned int H = 32;
        };
    }
}

#endif /* __PLATFORM_KEYMATRIX_APD5585_GOSSENMETRAWATT_HPP__ */
