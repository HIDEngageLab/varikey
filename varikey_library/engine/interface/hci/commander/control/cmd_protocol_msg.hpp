// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd protocol msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"

namespace engine::hci::cmd::protocol
{
    enum class RESULT : uint8_t
    {
        FAILURE = common::result::FAILURE,
        SUCCESS = common::result::SUCCESS,
        UNSUPPORTED = common::result::UNSUPPORTED,
        INVALID_COMMAND = common::result::CUSTOM,
    };

    struct message_t
    {
        RESULT result;
        chunk_t value;
    };

    extern void indication(message_t *const _msg, chunk_t const *const _chunk);
}
