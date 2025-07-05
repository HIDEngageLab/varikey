// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd keypad msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"

#include "payload_keypad.hpp"

namespace engine::hci::cmd::keypad
{
    enum class RESULT : uint8_t
    {
        ERROR = common::result::ERROR,
        FAILURE = common::result::FAILURE,
        SUCCESS = common::result::SUCCESS,
        UNKNOWN = common::result::UNKNOWN,
        UNSUPPORTED = common::result::UNSUPPORTED,

        WRONG_FUNCTION = common::result::CUSTOM + 1,
        WRONG_IDENTIFIER = common::result::CUSTOM,
        WRONG_SOURCE = common::result::CUSTOM + 3,
        WRONG_VALUE = common::result::CUSTOM + 2,
    };

    struct message_t
    {
        RESULT result;
        payload::keypad::content_t keypad;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
    extern void indication(message_t *const _msg);
}
