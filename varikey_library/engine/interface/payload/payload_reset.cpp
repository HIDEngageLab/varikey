// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload reset module
// SPDX-FileType: SOURCE

#include "payload_reset.hpp"

using namespace engine::payload::reset;

void content_t::deserialize(uint8_t const *const _space)
{
    function = static_cast<const FUNCTION>(_space[0]);
    if (!(function == FUNCTION::SHUTDOWN ||
          function == FUNCTION::FORMAT))
    {
        function = FUNCTION::UNDEFINED;
    }
}
void content_t::serialize(uint8_t **_ptr) const
{
    if ((function == FUNCTION::SHUTDOWN ||
         function == FUNCTION::FORMAT))
    {
        *(*_ptr)++ = (uint8_t)function;
    }
    else
    {
        *(*_ptr)++ = (uint8_t)FUNCTION::UNDEFINED;
    }
}
