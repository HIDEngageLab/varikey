// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix handler adp5585 functionality
// SPDX-FileType: SOURCE

#pragma once

#include "keymatrix_event_adp5585.hpp"
#include "keypad_keycode.hpp"

namespace platform::hardware
{
    enum TRIGGER
    {
        UP,
        DN,
        UNDEFINED,
    };
    struct KeymatrixHandlerAdp5585
    {
        virtual void event_handler(const platform::hardware::adp5585::event_t) = 0;

        void push_wheel_turn(const TRIGGER, const engine::keypad::STATE);
    };
}
