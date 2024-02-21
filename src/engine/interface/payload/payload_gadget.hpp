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

            const uint8_t GADGET_ID = to_underlying(payload::IDENTIFIER::GADGET);

            /** \brief Gadget status function value */
            enum class COMMAND : uint8_t
            {
                GET = common::function::GET,

                MOUNT = GADGET_ID + 1,
                RESUME = GADGET_ID + 4,
                SUSPEND = GADGET_ID + 3,
                UNMOUNT = GADGET_ID + 2,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                COMMAND command;
                MODE mode;

                static const size_t size() { return 2; }
                void deserialize(uint8_t const *const _space)
                {
                    command = static_cast<const COMMAND>(_space[0]);
                    if (!(command == COMMAND::MOUNT ||
                          command == COMMAND::RESUME ||
                          command == COMMAND::SUSPEND ||
                          command == COMMAND::UNMOUNT))
                    {
                        command = COMMAND::UNDEFINED;
                    }
                    mode = MODE::UNDEFINED;
                }

                void serialize(uint8_t *const _space) const
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)command;
                    if (mode == MODE::ACTIVE ||
                        mode == MODE::IDLE ||
                        mode == MODE::PENDING)
                    {
                        *ptr++ = (uint8_t)mode;
                    }
                    else
                    {
                        *ptr++ = (uint8_t)MODE::UNDEFINED;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_GADGET_HPP__
