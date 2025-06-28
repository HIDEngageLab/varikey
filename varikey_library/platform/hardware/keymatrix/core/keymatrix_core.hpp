/**
 * \file adp5585.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <cstdlib>

namespace platform::hardware
{
    extern void protocol_core_init(int const _address);
    extern bool protocol_core_has_event();
    extern void protocol_core_get_event(uint8_t *const _state, uint8_t *const _identifier);
}