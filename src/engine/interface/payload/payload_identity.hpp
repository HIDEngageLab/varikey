/**
 * \file payload_identity.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_IDENTITY_HPP__
#define __PAYLOAD_IDENTITY_HPP__

#include <cstdint>
#include <cstring>
#include <iostream>

#include "identity.hpp"
#include "param_maintainer.hpp"
#include "param_serial_number.hpp"
#include "payload_identifier.hpp"
#include "revision.h"

namespace engine
{
    namespace payload
    {
        namespace identity
        {
            enum class FUNCTION : uint8_t
            {
                GET = common::function::GET,
                SET = common::function::SET,

                UNDEFINED = 0xff,
            };

            enum class PART : uint8_t
            {
                FIRMWARE = 0,
                HARDWARE = 1,
                PLATFORM = 2,
                PRODUCT = 3,
                SERIAL = 4,
                UNIQUE = 5,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct content_t
            {
                FUNCTION function;
                PART part;

                const size_t size() const;
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_IDENTITY_HPP__