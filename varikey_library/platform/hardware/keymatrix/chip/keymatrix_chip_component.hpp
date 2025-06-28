/**
 * \file keymatrix_adp5585.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

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
