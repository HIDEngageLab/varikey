/**
 * \file identity.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __VARIKEY_IDENTITY_HPP__
#define __VARIKEY_IDENTITY_HPP__

#include <cstdint>
#include <cstdlib>

namespace identity
{
    namespace firmware
    {
        static const size_t SIZE{10};

        union content_t
        {
            uint8_t byte[SIZE];
            struct
            {
                uint16_t identifier;
                uint16_t revision;
                uint16_t patch;
                uint16_t build;
                uint16_t vendor;
            };
        } __attribute__((packed));
    }

    namespace hardware
    {
        static const size_t SIZE{6};

        union content_t
        {
            uint8_t byte[SIZE];
            struct
            {
                uint16_t maintainer;
                uint16_t identifier;
                uint8_t number;
                uint8_t variant;
            };
        } __attribute__((packed));
    }
}

#endif /* __VARIKEY_IDENTITY_HPP__ */
