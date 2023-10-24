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
        void Gossenmetrawatt_1_0::initialize()
        {
            BoardKeypad::initialize();
        }

        void Gossenmetrawatt_1_0::shutdown()
        {
            BoardKeypad::shutdown();
        }
    }
}
