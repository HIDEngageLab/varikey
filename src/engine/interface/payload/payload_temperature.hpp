/**
 * \file payload_temperature.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_TEMPERATURE_HPP__
#define __PAYLOAD_TEMPERATURE_HPP__

#include <cstdint>
#include <cstdlib>

#include "engine_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace temperature
        {
            /** \brief Status request/confirmation function value */
            enum class FUNCTION : uint8_t
            {
                GET = common::function::GET,

                ALARM = common::function::CUSTOM,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                static const size_t size() { return 2; }

                FUNCTION function;
                float value;

                void deserialize(uint8_t const *const _space)
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

                void serialize(uint8_t **_ptr) const
                {
                    if (function == FUNCTION::GET ||
                        function == FUNCTION::ALARM)
                    {
                        *(*_ptr)++ = (uint8_t)function;
                        serialize_float(value, _ptr);
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_TEMPERATURE_HPP__
