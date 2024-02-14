/**
 * \file payload_reset.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_RESET_HPP__
#define __PAYLOAD_RESET_HPP__

#include <cstdint>
#include <cstdlib>

#include "engine_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace reset
        {
            /** \brief Status request/confirmation function value */
            enum class FUNCTION : uint8_t
            {
                SHUTDOWN = common::function::CUSTOM,
                FORMAT = common::function::CUSTOM + 1,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                FUNCTION function;

                static const size_t size() { return 2; }
                void deserialize(uint8_t const *const _space)
                {
                    function = static_cast<const FUNCTION>(_space[0]);
                    if (!(function == FUNCTION::SHUTDOWN ||
                          function == FUNCTION::FORMAT))
                    {
                        function = FUNCTION::UNDEFINED;
                    }
                }
                void serialize(uint8_t *const _space) const
                {
                    uint8_t *ptr = _space;
                    if ((function == FUNCTION::SHUTDOWN ||
                         function == FUNCTION::FORMAT))
                    {
                        *ptr++ = (uint8_t)function;
                    }
                    else
                    {
                        *ptr++ = (uint8_t)FUNCTION::UNDEFINED;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_RESET_HPP__
