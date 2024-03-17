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

            struct __attribute__((packed)) content_t
            {
                FUNCTION function;
                PART part;

                const size_t size()
                {
                    switch (part)
                    {
                    case PART::FIRMWARE:
                        return 2 + ::identity::firmware::SIZE;
                    case PART::HARDWARE:
                        return 2 + ::identity::hardware::SIZE;
                    case PART::PRODUCT:
                        return 2 + strlen(::identity::firmware::PRODUCT);
                    case PART::PLATFORM:
                        return 2 + strlen(::identity::hardware::PLATFORM);
                    case PART::SERIAL:
                        return 2 + registry::parameter::serial_number::SIZE;
                    case PART::UNIQUE:
                        return 2 + sizeof(uint32_t);
                    default:
                        break;
                    }
                    return 2;
                }

                void deserialize(uint8_t const *const _space)
                {
                    function = static_cast<const FUNCTION>(_space[0]);
                    part = static_cast<const PART>(_space[1]);
                    switch (part)
                    {
                    case PART::FIRMWARE:
                        break;
                    case PART::HARDWARE:
                        break;
                    case PART::PRODUCT:
                        break;
                    case PART::PLATFORM:
                        break;
                    case PART::SERIAL:
                        if (function == FUNCTION::SET)
                        {
                            registry::parameter::serial_number::g_register.deserialize(&_space[1]);
                        }
                        break;
                    case PART::UNIQUE:
                        break;
                    default:
                        part = PART::UNDEFINED;
                    }
                }

                void serialize(uint8_t **_ptr) const
                {
                    *(*_ptr)++ = (uint8_t)function;
                    *(*_ptr)++ = (uint8_t)part;

                    switch (part)
                    {
                    case PART::FIRMWARE:
                        serialize_word(::identity::firmware::IDENTIFIER, _ptr);
                        serialize_word(::identity::firmware::REVISION, _ptr);
                        serialize_word(::identity::firmware::PATCH, _ptr);
                        serialize_word(::identity::firmware::BUILD, _ptr);
                        serialize_word(::identity::firmware::VENDOR, _ptr);
                        /*
                        for (size_t i = 0; i < ::identity::firmware::FIRMWARE_HASH_SIZE; ++i)
                            *(*_ptr)++ = ::identity::firmware::FIRMWARE_HASH[i];
                        */
                        break;
                    case PART::HARDWARE:
                        serialize_word(registry::parameter::maintainer::g_register.word, _ptr);
                        serialize_word(::identity::hardware::IDENTIFIER, _ptr);
                        *(*_ptr)++ = ::identity::hardware::NUMBER;
                        *(*_ptr)++ = ::identity::hardware::VARIANT;
                        break;
                    case PART::PRODUCT:
                    {
                        const size_t string_length = strlen(::identity::firmware::PRODUCT);
                        memcpy(*_ptr, ::identity::firmware::PRODUCT, string_length);
                        (*_ptr) += string_length;
                        break;
                    }
                    case PART::PLATFORM:
                    {
                        const size_t string_length = strlen(::identity::hardware::PLATFORM);
                        memcpy(*_ptr, ::identity::hardware::PLATFORM, string_length);
                        (*_ptr) += string_length;
                        break;
                    }
                    case PART::SERIAL:
                        registry::parameter::serial_number::g_register.serialize(_ptr);
                        break;
                    case PART::UNIQUE:
                        serialize_long(registry::parameter::serial_number::g_unique_key, _ptr);
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