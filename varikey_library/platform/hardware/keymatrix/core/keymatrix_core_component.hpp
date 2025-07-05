// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix core component functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"

namespace platform::hardware
{
    struct KeymatrixCore : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        bool perform(void);
    };
}
