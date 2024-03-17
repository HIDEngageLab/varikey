/**
 * \file cmd_display_msg.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __CMD_DISPLAY_MSG_HPP__
#define __CMD_DISPLAY_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

#include "display_font.hpp"
#include "display_image.hpp"
#include "payload_display.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace display
            {
                using content_t = engine::payload::display::content_t;

                /** \brief Display message result code */
                enum class RESULT : uint8_t
                {
                    SUCCESS = common::result::SUCCESS,
                    FAILURE = common::result::FAILURE,
                    UNKNOWN = common::result::UNKNOWN,
                    WRONG_POSITION = common::result::CUSTOM,
                };

                /**
                    \brief Display req/cfm message
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

#endif // __CMD_DISPLAY_MSG_HPP__
