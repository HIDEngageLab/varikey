// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload gpio module
// SPDX-FileType: SOURCE

#include "payload_gpio.hpp"

using namespace engine::payload::gpio;

void content_t::deserialize(uint8_t const *const _space)
{
    function = static_cast<FUNCTION>(_space[0]);
    if (!(function == FUNCTION::DISABLE ||
          function == FUNCTION::ENABLE ||
          function == FUNCTION::DIRECTION ||
          function == FUNCTION::IN ||
          function == FUNCTION::OUT ||
          function == FUNCTION::VALUE ||
          function == FUNCTION::HIGH ||
          function == FUNCTION::LOW))
    {
        function = FUNCTION::UNDEFINED;
    }

    identifier = static_cast<const IDENTIFIER>(_space[1]);
    if (!(identifier == IDENTIFIER::GPIO0 ||
          identifier == IDENTIFIER::GPIO1 ||
          identifier == IDENTIFIER::GPIO2 ||
          identifier == IDENTIFIER::GPIO3))
    {
        identifier = IDENTIFIER::UNDEFINED;
    }
}

void content_t::serialize(uint8_t **_ptr) const
{
    *(*_ptr)++ = (uint8_t)function;
    *(*_ptr)++ = (uint8_t)identifier;
}
