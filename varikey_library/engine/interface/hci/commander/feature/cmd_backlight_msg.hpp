// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd backlight msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"

#include "backlight_program.hpp"
#include "payload_backlight.hpp"
#include "smartled_color.hpp"

namespace engine::hci::cmd::backlight
{
    using content_t = engine::payload::backlight::content_t;

    enum class RESULT : uint8_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
        WRONG_MODE = common::result::CUSTOM,
        WRONG_CHANNEL = common::result::CUSTOM + 1,
        WRONG_COLOR = common::result::CUSTOM + 2,
    };

    struct message_t
    {
        RESULT result;
        content_t content;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
}
