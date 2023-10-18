/**
 * \file board_gossenmetrawatt_1_0.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "board_gossenmetrawatt_1_0.hpp"

namespace platform
{
    namespace board
    {
        Gossenmetrawatt_1_0::Gossenmetrawatt_1_0()
        {
        }

        Gossenmetrawatt_1_0::~Gossenmetrawatt_1_0()
        {
        }

        const int Gossenmetrawatt_1_0::getIdentifier() const
        {
            return 0x0210;
        }
    }
}
