// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload gpio module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstdlib>

#include "board_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine::payload::gpio
{
    using IDENTIFIER = platform::board::IDENTIFIER;
    using DIRECTION = platform::board::DIRECTION;
    using VALUE = platform::board::VALUE;

    enum class FUNCTION : uint8_t
    {
        DISABLE = common::function::DISABLE,
        ENABLE = common::function::ENABLE,

        DIRECTION = common::function::CUSTOM,
        IN = common::function::CUSTOM + 1,
        OUT = common::function::CUSTOM + 2,
        VALUE = common::function::CUSTOM + 3,
        HIGH = common::function::CUSTOM + 4,
        LOW = common::function::CUSTOM + 5,

        UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
    };

    struct content_t
    {
        FUNCTION function;
        IDENTIFIER identifier;
        uint32_t diff;

        static const size_t size() { return 2; }
        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    };
}
