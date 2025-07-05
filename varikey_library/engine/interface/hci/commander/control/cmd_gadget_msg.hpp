// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd gadget msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"
#include "payload_gadget.hpp"

namespace engine::hci::cmd::gadget
{
    using content_t = payload::gadget::content_t;

    enum class RESULT : uint8_t
    {
        FAILURE = common::result::FAILURE,
        SUCCESS = common::result::SUCCESS,
        UNKNOWN = common::result::UNKNOWN,
        UNSUPPORTED = common::result::UNSUPPORTED,

        WRONG_STATE = common::result::CUSTOM,
    };

    struct message_t
    {
        RESULT result;
        content_t gadget;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
    extern void indication(message_t *const _msg);
}
