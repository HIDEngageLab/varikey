/**
 * \file payload_gadget.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_gadget.hpp"

using namespace engine::payload::gadget;

void content_t::deserialize(uint8_t const *const _space)
{
    function = static_cast<const FUNCTION>(_space[0]);
    if (function == FUNCTION::GET ||
        function == FUNCTION::MOUNT ||
        function == FUNCTION::RESUME ||
        function == FUNCTION::SUSPEND ||
        function == FUNCTION::UNMOUNT)
    {
        /* do nothing */
    }
    else
    {
        function = FUNCTION::UNDEFINED;
    }
    state = STATE::UNDEFINED;
}

void content_t::serialize(uint8_t **_ptr) const
{
    *(*_ptr)++ = (uint8_t)function;
    if (state == STATE::ACTIVE ||
        state == STATE::IDLE ||
        state == STATE::PENDING ||
        state == STATE::SUSPEND)
    {
        *(*_ptr)++ = (uint8_t)state;
    }
    else
    {
        *(*_ptr)++ = (uint8_t)STATE::UNDEFINED;
    }
}
