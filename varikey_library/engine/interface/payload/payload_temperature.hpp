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

            struct content_t
            {
                FUNCTION function;
                float value;

                const size_t size() const { return 2; }
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_TEMPERATURE_HPP__
