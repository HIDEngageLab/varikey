// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware keymatrix scanner functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"

namespace platform::hardware
{
    struct KeymatrixScanner : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        bool perform(void);
    };
}
