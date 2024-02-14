/**
 * \file payload_parameter.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_PARAMETER_HPP__
#define __PAYLOAD_PARAMETER_HPP__

#include <cstdint>
#include <cstdlib>

#include "chunk.h"
#include "engine_defines.hpp"
#include "macros.hpp"
#include "param_backlight.hpp"
#include "parameter.hpp"
#include "payload_identifier.hpp"
#include "registry_interface.hpp"

namespace engine
{
    namespace payload
    {
        namespace parameter
        {
            using IDENTIFIER = registry::parameter::IDENTIFIER;

            /** \brief Parameter length type */
            enum class TYPELEN : uint8_t
            {
                BYTE = 0x01,
                WORD = 0x02,
                LONG = 0x04,
                BUFF = 0x80,
            };

            /** \brief parameter request function type */
            enum class FUNCTION : uint8_t
            {
                GET = common::function::GET,
                SET = common::function::SET,

                UNDEFINED = common::function::UNDEFINED,
            };

            struct __attribute__((packed)) content_t
            {
                static const size_t size() { return 2; }

                IDENTIFIER identifier;
                FUNCTION function;
                chunk_t value;

                void deserialize(uint8_t const *const _space)
                {
                    identifier = registry::parameter::to_identifier(_space[0]);
                    function = static_cast<FUNCTION>(_space[1]);
                }

                void serialize(uint8_t *const _space)
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)identifier;
                    *ptr++ = (uint8_t)function;
                    for (size_t i = 0; i < value.size; ++i)
                    {
                        *ptr++ = value.space[i];
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_PARAMETER_HPP__
