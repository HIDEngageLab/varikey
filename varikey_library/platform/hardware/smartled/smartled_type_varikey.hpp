// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware smartled varikey functionality
// SPDX-FileType: SOURCE

#pragma once

#include "smartled.hpp"
#include "smartled_mapper.hpp"

namespace platform::hardware::smartled
{
    struct VarikeyPrototype : public FrontChannel
    {
        static const unsigned int PIO_PIN = 22;
        static const std::size_t LED_COUNT = 3;

        using Mapper = smartled::LedMapper<
            smartled::INDEX::FIRST,
            smartled::INDEX::SECOND,
            smartled::INDEX::THIRD>;
    };
}
