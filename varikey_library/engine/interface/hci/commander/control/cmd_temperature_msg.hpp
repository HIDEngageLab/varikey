// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd temperature msg module
// SPDX-FileType: SOURCE

#pragma once

#include "macros.hpp"
#include "payload_temperature.hpp"

namespace engine::hci::cmd::temperature
{
    using content_t = engine::payload::temperature::content_t;

    enum class RESULT : uint8_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
        UNSUPPORTED = common::result::UNSUPPORTED,
        UNKNOWN = common::result::UNKNOWN,
    };

    struct message_t
    {
        RESULT result;
        content_t content;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
    extern void indication(message_t *const _msg);
}
