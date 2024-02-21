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
            const uint8_t IDENTITY_ID = to_underlying(payload::IDENTIFIER::IDENTITY);

            enum class IDENTIFIER : uint8_t
            {
                FIRMWARE = IDENTITY_ID + 1,
                HARDWARE = IDENTITY_ID + 2,
                PLATFORM = IDENTITY_ID + 4,
                PRODUCT = IDENTITY_ID + 3,
                SERIAL = IDENTITY_ID + 5,
                UNIQUE = IDENTITY_ID + 6,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            struct __attribute__((packed)) content_t
            {
                IDENTIFIER identifier;

                const size_t size()
                {
                    switch (identifier)
                    {
                    case IDENTIFIER::FIRMWARE:
                        return ::identity::firmware::SIZE;
                    case IDENTIFIER::HARDWARE:
                        return ::identity::hardware::SIZE;
                    case IDENTIFIER::PRODUCT:
                        return strlen(::identity::firmware::PRODUCT);
                    case IDENTIFIER::PLATFORM:
                        return strlen(::identity::hardware::PLATFORM);
                    case IDENTIFIER::SERIAL:
                        return registry::parameter::serial_number::SIZE;
                    case IDENTIFIER::UNIQUE:
                        return sizeof(uint32_t);
                    default:
                        break;
                    }
                    return 0;
                }

                void deserialize(uint8_t const *const _space)
                {
                    identifier = static_cast<const IDENTIFIER>(_space[0]);
                    switch (identifier)
                    {
                    case IDENTIFIER::FIRMWARE:
                        break;
                    case IDENTIFIER::HARDWARE:
                        break;
                    case IDENTIFIER::PRODUCT:
                        break;
                    case IDENTIFIER::PLATFORM:
                        break;
                    case IDENTIFIER::SERIAL:
                        registry::parameter::serial_number::g_register.deserialize(&_space[1]);
                        break;
                    case IDENTIFIER::UNIQUE:
                        break;
                    default:
                        identifier = IDENTIFIER::UNDEFINED;
                    }
                }

                void serialize(uint8_t *const _space) const
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)identifier;

                    switch (identifier)
                    {
                    case IDENTIFIER::FIRMWARE:
                        serialize_word(::identity::firmware::IDENTIFIER, &ptr);
                        serialize_word(::identity::firmware::REVISION, &ptr);
                        serialize_word(::identity::firmware::PATCH, &ptr);
                        serialize_word(::identity::firmware::BUILD, &ptr);
                        serialize_word(::identity::firmware::VENDOR, &ptr);
                        break;
                    case IDENTIFIER::HARDWARE:
                        serialize_word(registry::parameter::maintainer::g_register.word, &ptr);
                        serialize_word(::identity::hardware::IDENTIFIER, &ptr);
                        *ptr++ = ::identity::hardware::NUMBER;
                        *ptr++ = ::identity::hardware::VARIANT;
                        break;
                    case IDENTIFIER::PRODUCT:
                        memcpy(ptr, ::identity::firmware::PRODUCT, strlen(::identity::firmware::PRODUCT));
                        break;
                    case IDENTIFIER::PLATFORM:
                        memcpy(_space, ::identity::hardware::PLATFORM, strlen(::identity::hardware::PLATFORM));
                        break;
                    case IDENTIFIER::SERIAL:
                        registry::parameter::serial_number::g_register.serialize(ptr);
                        break;
                    case IDENTIFIER::UNIQUE:
                        serialize_long(registry::parameter::serial_number::g_unique_key, &ptr);
                        break;
                    default:
                        break;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_IDENTITY_HPP__