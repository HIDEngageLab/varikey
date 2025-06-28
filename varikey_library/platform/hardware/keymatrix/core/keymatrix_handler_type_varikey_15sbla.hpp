/**
 * \file keymatrix_adp5585_handler_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_core_event.hpp"
#include "keymatrix_core_handler.hpp"

namespace platform::hardware
{
    struct KeymatrixHandlerVarikey15SBLA : public KeymatrixHandlerCore
    {
        void event_handler(const platform::hardware::pico::event_t);
    };
}
