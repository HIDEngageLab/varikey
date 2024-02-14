/**
 * \file cmd_reset_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Reset message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "chunk.h"
#include "cmd_reset_msg.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace reset
            {
                static const size_t IND_SIZE = 2;

                /**
                    \brief Reset request message

                    (Message handling isn't required here)
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    (void)_chunk;
                    assert(_msg != NULL); // reset request message null

                    /* handle */
                    _msg->result = RESULT::SUCCESS;

                    _msg->content.deserialize(_chunk->space);

                    _msg->value.size = 0;
                    _msg->value.space = 0;
                }

                /**
                    \brief Reset indication message
                */
                extern void indication(message_t *const _msg)
                {
                    assert(_msg != NULL); /* command control reset message null */

                    /* handle */
                    uint8_t space[IND_SIZE] = {0};
                    _msg->value.size = IND_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::RESET_IND;
                    *ptr++ = (uint8_t)_msg->result;

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}