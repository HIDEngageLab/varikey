// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix chip keymatrix chip component functionality
// SPDX-FileType: SOURCE

#pragma once

#include "component_interface.hpp"

namespace platform::hardware
{
    struct KeymatrixApd5585 : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        bool perform(void);
    };
}
