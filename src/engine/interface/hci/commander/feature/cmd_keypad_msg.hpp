/**
 * \file cmd_keypad_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Event message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_KEYPAD_MSG_HPP__
#define __CMD_KEYPAD_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

#include "payload_keycode.hpp"
#include "payload_keypad.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace keypad
            {
                /** \brief Event result */
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

                /**
                    \brief Event message

                    Event request und confirmation
                    Trigger indication
                */
                struct message_t
                {
                    RESULT result;
                    union
                    {
                        payload::keycode::content_t keycode;
                        payload::keypad::content_t keypad;
                    };
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
                extern void indication(message_t *const _msg);
            }
        }
    }
}

#endif /* __CMD_KEYPAD_MSG_HPP__ */
