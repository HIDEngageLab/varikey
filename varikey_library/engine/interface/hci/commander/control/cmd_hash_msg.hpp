// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd hash msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"

namespace engine::hci::cmd::hash
{
    enum class RESULT : uint8_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
    };

    struct message_t
    {
        RESULT result;
        uint16_t hash;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
}
