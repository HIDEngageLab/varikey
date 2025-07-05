// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd identity msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"
#include "payload_identity.hpp"

namespace engine::hci::cmd::identity
{
    using content_t = engine::payload::identity::content_t;

    enum class RESULT : uint8_t
    {
        FAILURE = common::result::FAILURE,
        SUCCESS = common::result::SUCCESS,
        UNKNOWN = common::result::UNKNOWN,
        UNSUPPORTED = common::result::UNSUPPORTED,
    };

    struct message_t
    {
        content_t identity;
        RESULT result;

        chunk_t value;
    };

    extern void request(chunk_t const *_chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
}
