// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix core handler functionality
// SPDX-FileType: SOURCE

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
