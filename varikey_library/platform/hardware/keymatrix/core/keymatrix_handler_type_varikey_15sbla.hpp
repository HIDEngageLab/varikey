// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix handler type varikey 15sbla functionality
// SPDX-FileType: SOURCE

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
