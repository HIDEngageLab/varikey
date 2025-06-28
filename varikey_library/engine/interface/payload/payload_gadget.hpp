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
            using STATE = engine::defines::STATE;

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

            struct content_t
            {
                FUNCTION function;
                STATE state;

                const size_t size() const { return 2; }
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_GADGET_HPP__
