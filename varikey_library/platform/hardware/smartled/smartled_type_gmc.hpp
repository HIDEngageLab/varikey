// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled GMCI functionality
// SPDX-FileType: SOURCE

#pragma once

#include "smartled.hpp"
#include "smartled_mapper.hpp"

namespace platform::hardware::smartled
{
    struct GMCI1 : public FrontChannel
    {
        static const unsigned int PIO_PIN = 20;
        static const std::size_t LED_COUNT = 3;

        using Mapper = smartled::LedMapper<
            smartled::INDEX::FIRST,
            smartled::INDEX::THIRD,
            smartled::INDEX::SECOND>;
    };
}
