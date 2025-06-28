/**
 * \file cmd_hash_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Key message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "checksum.hpp"
#include "cmd_hash_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace hash
            {
                static const size_t CFM_SIZE = 4;

                /**
                    \brief Key request message

                    Deserialize only
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    /* checks */
                    assert(_chunk != NULL && _msg != NULL); /* key request chunk null */

                    /* deserialize */
                    _msg->result = RESULT::SUCCESS;
                    _msg->hash = checksum_crc(_chunk, 0);

                    _msg->value.size = 0;
                    _msg->value.space = 0;
                }

                /**
                    \brief Key confirmation message
                */
                extern void confirmation(message_t *const _msg)
                {
                    /* checks */
                    assert(_msg != NULL); /* key confirmation message null */

                    /* handle */
                    uint8_t space[CFM_SIZE] = {0};
                    _msg->value.size = CFM_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::HASH_CFM;
                    *ptr++ = (uint8_t)_msg->result;
                    serialize_word(_msg->hash, &ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}