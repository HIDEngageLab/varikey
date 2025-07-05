// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: payload temperature module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>
#include <cstdlib>

#include "engine_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine::payload::temperature
{
    enum class FUNCTION : uint8_t
    {
        GET = common::function::GET,

        ALARM = common::function::CUSTOM,

        UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
    };

    struct content_t
    {
        FUNCTION function;
        float value;

        const size_t size() const { return 2; }
        void deserialize(uint8_t const *const);
        void serialize(uint8_t **) const;
    };
}
