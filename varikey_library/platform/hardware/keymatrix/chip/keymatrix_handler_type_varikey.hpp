// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix handler type varikey functionality
// SPDX-FileType: SOURCE

#pragma once

#include "keymatrix_event_adp5585.hpp"
#include "keymatrix_handler_adp5585.hpp"

namespace platform::hardware
{
    struct KeymatrixHandlerVarikey : public KeymatrixHandlerAdp5585
    {
        void event_handler(const platform::hardware::adp5585::event_t);
    };
}
