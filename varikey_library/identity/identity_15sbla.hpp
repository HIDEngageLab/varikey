/**
 * \file identity_10bwdb.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace engine
{
    namespace identity
    {
        struct Identity15SBLA
        {
            static const uint16_t IDENTIFIER_DEFAULT = 0x0000;
            static const uint16_t HW_REVISION_DEFAULT = 0;
            static const uint16_t FW_REVISION_DEFAULT = 0;

            static constexpr float MAGIC_LATITUDE = 49.42877325078828f;
            static constexpr float MAGIC_LONGITUDE = 11.020437994105766f;
        };
    }
}
