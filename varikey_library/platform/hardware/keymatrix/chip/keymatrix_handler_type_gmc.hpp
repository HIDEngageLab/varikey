/**
 * \file keymatrix_adp5585_handler_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_event_adp5585.hpp"
#include "keymatrix_handler_adp5585.hpp"

namespace platform::hardware
{
    struct KeymatrixHandlerGmc : public KeymatrixHandlerAdp5585
    {
        void event_handler(const platform::hardware::adp5585::event_t);
    };
}
