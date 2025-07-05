// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled type functionality
// SPDX-FileType: SOURCE

#pragma once

#include <array>

namespace platform::hardware::smartled
{
    enum class INDEX
    {
        FIRST = 0,
        SECOND,
        THIRD,
        FOURTH,
        FIFTH,
        SIXTH,
        SEVENTH,
        EIGHTH,
        NINTH,
        TENTH,
        ELEVENTH,
        TWELFTH,
        THIRTEENTH,
        FOURTEENTH,
        FIFTEENTH,
        SIXTEENTH,
        SEVENTEENTH,
        EIGHTEENTH,
        NINETEENTH,
        TWENTIETH
    };

    template <INDEX... MappedOrder>
    struct LedMapper
    {
        static constexpr std::array<INDEX, sizeof...(MappedOrder)> mapping = {MappedOrder...};
        static constexpr size_t size() { return mapping.size(); }
    };
}
