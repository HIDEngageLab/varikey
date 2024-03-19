/**
 * \file payload_temperature.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_temperature.hpp"

using namespace engine::payload::temperature;

void content_t::deserialize(uint8_t const *const _space)
{
    uint8_t const *ptr = _space;
    function = static_cast<const FUNCTION>(*ptr++);
    if (!(function == FUNCTION::GET ||
          function == FUNCTION::ALARM))
    {
        function = FUNCTION::UNDEFINED;
    }
    if (function == FUNCTION::ALARM)
    {
        value = deserialize_float(&ptr);
    }
}

void content_t::serialize(uint8_t **_ptr) const
{
    if (function == FUNCTION::GET ||
        function == FUNCTION::ALARM)
    {
        *(*_ptr)++ = (uint8_t)function;
        serialize_float(value, _ptr);
    }
}
