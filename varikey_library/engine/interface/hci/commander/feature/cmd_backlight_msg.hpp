/**
 * \file cmd_backlight_msg.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __CMD_BACKLIGHT_MSG_HPP__
#define __CMD_BACKLIGHT_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

#include "backlight_color.hpp"
#include "backlight_mode.hpp"
#include "payload_backlight.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace backlight
            {
                using content_t = engine::payload::backlight::content_t;

                /** \brief Backlight message result code */
                enum class RESULT : uint8_t
                {
                    SUCCESS = common::result::SUCCESS,
                    FAILURE = common::result::FAILURE,
                    WRONG_MODE = common::result::CUSTOM,
                };

                /**
                    \brief Backlight req/cfm message
                */
                struct message_t
                {
                    RESULT result;
                    content_t content;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
            }
        }
    }
}

#endif // __CMD_BACKLIGHT_MSG_HPP__
