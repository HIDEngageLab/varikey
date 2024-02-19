/**
 * \file keymatrix_adp5585_handler.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_KEYMATRIX_ADP5585_HANDLER_HPP__
#define __PLATFORM_KEYMATRIX_ADP5585_HANDLER_HPP__

#include "keymatrix_adp5585_event.hpp"
#include "keypad_keycode.hpp"

namespace platform
{
    namespace hardware
    {
        enum TRIGGER
        {
            UP,
            DN,
            UNDEFINED,
        };

        struct KeymatrixHandler
        {
            virtual void event_handler(const platform::hardware::adp5585::event_t) = 0;

            void push_wheel_turn(const TRIGGER, const engine::keypad::STATE);
        };
    }
}

#endif // __PLATFORM_KEYMATRIX_ADP5585_HANDLER_HPP__
