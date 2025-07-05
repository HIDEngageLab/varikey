// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled varikey 15sbla functionality
// SPDX-FileType: SOURCE

#pragma once

#include "smartled.hpp"
#include "smartled_mapper.hpp"

namespace platform::hardware::smartled
{
    struct VarikeyBack15SBLA : public BackChannel
    {
        static const unsigned int PIO_PIN = 6;
        static const std::size_t LED_COUNT = 5;
        using Mapper = smartled::LedMapper<
            smartled::INDEX::FIRST,
            smartled::INDEX::SECOND,
            smartled::INDEX::THIRD,
            smartled::INDEX::FOURTH,
            smartled::INDEX::FIFTH>;
    };

    struct VarikeyFront15SBLA : public FrontChannel
    {
        static const unsigned int PIO_PIN = 7;
        static const std::size_t LED_COUNT = 15;
        using Mapper = smartled::LedMapper<
            smartled::INDEX::FIFTH,
            smartled::INDEX::SEVENTH,
            smartled::INDEX::SIXTH,
            smartled::INDEX::FOURTH,
            smartled::INDEX::THIRD,
            smartled::INDEX::SECOND,
            smartled::INDEX::FIRST,
            smartled::INDEX::EIGHTH,
            smartled::INDEX::TENTH,
            smartled::INDEX::THIRTEENTH,
            smartled::INDEX::NINTH,
            smartled::INDEX::TWELFTH,
            smartled::INDEX::FIFTEENTH,
            smartled::INDEX::ELEVENTH,
            smartled::INDEX::FOURTEENTH>;
    };
}
