/**
 * \file component_state.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PULP_COMPONENT_STATE_HPP__
#define __PULP_COMPONENT_STATE_HPP__

#include <stdint.h>

namespace pulp
{
    enum class COMPONENT_STATE : uint8_t
    {
        IDLE = 0x00,
        ACTIVE = 0x01,
        PENDING = 0x02,
        UNDEFINED = 0xff,
    };
}

#endif // __PULP_COMPONENT_STATE_HPP__
