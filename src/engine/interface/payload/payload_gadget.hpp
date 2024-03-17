/**
 * \file payload_gadget.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_GADGET_HPP__
#define __PAYLOAD_GADGET_HPP__

#include <cstdint>
#include <cstdlib>

#include "engine_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace gadget
        {
            using MODE = engine::defines::STATE;

            /** \brief Gadget status function value */
            enum class FUNCTION : uint8_t
            {
                GET = common::function::GET,

                MOUNT = common::function::CUSTOM,
                RESUME = common::function::CUSTOM + 1,
                SUSPEND = common::function::CUSTOM + 2,
                UNMOUNT = common::function::CUSTOM + 3,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                FUNCTION function;
                MODE mode;

                static const size_t size() { return 2; }
                void deserialize(uint8_t const *const _space)
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
                    mode = MODE::UNDEFINED;
                }

                void serialize(uint8_t **_ptr) const
                {
                    *(*_ptr)++ = (uint8_t)function;
                    if (mode == MODE::ACTIVE ||
                        mode == MODE::IDLE ||
                        mode == MODE::PENDING ||
                        mode == MODE::SUSPEND)
                    {
                        *(*_ptr)++ = (uint8_t)mode;
                    }
                    else
                    {
                        *(*_ptr)++ = (uint8_t)MODE::UNDEFINED;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_GADGET_HPP__
