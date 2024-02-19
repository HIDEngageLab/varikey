/**
 * \file keymatrix_adp5585_handler_gossenmetrawatt.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_HANDLER_GOSSENMETRAWATT_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_HANDLER_GOSSENMETRAWATT_HPP__

#include "keymatrix_adp5585_event.hpp"
#include "keymatrix_adp5585_handler.hpp"

namespace platform
{
    namespace hardware
    {
        struct KeymatrixHandlerGossenmetrawatt : public KeymatrixHandler
        {
            void event_handler(const platform::hardware::adp5585::event_t);
        };
    }
}

#endif // __PLATFORM_KEYMATRIX_ADP5585_HANDLER_GOSSENMETRAWATT_HPP__
