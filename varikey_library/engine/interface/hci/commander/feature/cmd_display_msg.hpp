// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd display msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"

#include "display_font.hpp"
#include "display_image.hpp"
#include "payload_display.hpp"

namespace engine::hci::cmd::display
{
    using content_t = engine::payload::display::content_t;

    enum class RESULT : uint8_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
        UNKNOWN = common::result::UNKNOWN,
        WRONG_POSITION = common::result::CUSTOM,
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
