/**
 * \file board_varikey_1_0.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "board_varikey_1_0.hpp"

namespace platform
{
    namespace board
    {
        void Varikey_1_0::Varikey_1_0::initialize()
        {
            BoardKeypad::initialize();
        }

        void Varikey_1_0::Varikey_1_0::shutdown()
        {
            BoardKeypad::shutdown();
        }
    }
}
