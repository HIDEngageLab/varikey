// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: serial msg module
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "chunk.h"

namespace engine::serial::msg
{
    enum class TYPE : uint8_t
    {
        COMMANDER = 0x01,
        MONITORING = 0x02,
    };

    struct unit_t
    {
        TYPE type;
        chunk_t *payload;
    };

    extern void serialize(unit_t const *const _msg, chunk_t *const _chunk);
    extern void deserialize(unit_t *const _msg, chunk_t const *const _chunk);
}
