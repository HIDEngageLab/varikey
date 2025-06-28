/**
 * \file keymatrix_adp5585_handler.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "keymatrix_core_event.hpp"
#include "keypad_keycode.hpp"

namespace platform::hardware
{
    struct KeymatrixHandlerCore
    {
        virtual void event_handler(const platform::hardware::pico::event_t) = 0;
    };
}
