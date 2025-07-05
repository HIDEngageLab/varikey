// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd parameter msg module
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>

#include "chunk.h"
#include "macros.hpp"
#include "parameter.hpp"
#include "payload_parameter.hpp"
namespace engine::hci::cmd::param
{
    enum class RESULT : uint8_t
    {
        ERROR = common::result::ERROR,
        FAILURE = common::result::FAILURE,
        SUCCESS = common::result::SUCCESS,
        UNKNOWN = common::result::UNKNOWN,
        UNSUPPORTED = common::result::UNSUPPORTED,
    };

    struct message_t
    {
        RESULT result;
        payload::parameter::content_t content;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
}
