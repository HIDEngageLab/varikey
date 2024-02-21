/**
 * \file identity_demo.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_IDENTITY_DEMO_HPP__
#define __ENGINE_IDENTITY_DEMO_HPP__

#include <cstdint>

namespace engine
{
    namespace identity
    {
        struct IdentityDemo
        {
            static const uint16_t IDENTIFIER_DEFAULT = 0x0000;
            static const uint16_t HW_REVISION_DEFAULT = 0;
            static const uint16_t FW_REVISION_DEFAULT = 0;

            static constexpr float MAGIC_LATITUDE = 49.44162320135808f;
            static constexpr float MAGIC_LONGITUDE = 11.053797038031261f;
        };
    }
}

#define EMBEDDED_KEYBOARD

#endif // __ENGINE_IDENTITY_DEMO_HPP__
