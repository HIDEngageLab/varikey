// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload identity module
// SPDX-FileType: SOURCE

#include "payload_identity.hpp"

using namespace engine::payload::identity;

const size_t content_t::size(void) const
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

void content_t::deserialize(uint8_t const *const _space)
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

void content_t::serialize(uint8_t **_ptr) const
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
