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

        Varikey_1_0::Varikey_1_0()
        {
        }

        Varikey_1_0::~Varikey_1_0()
        {
        }

        const int Varikey_1_0::getIdentifier() const
        {
            return 0x0110;
        }

    }
}
