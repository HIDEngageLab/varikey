/**
 * \file cmd_temperature_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Temperature message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <limits>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "board.hpp"
#include "chunk.h"
#include "cmd_temperature_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace temperature
            {
                static const size_t CFM_SIZE = 6;
                static const size_t IND_SIZE = 5;

                /**
                    \brief Temperature request message

                    Deserialize only.
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    (void)_chunk;
                    assert(_msg != NULL); // message is not null

                    using FUNCTION = engine::payload::temperature::FUNCTION;

                    _msg->content.deserialize(_chunk->space);
                    if (_msg->content.function == FUNCTION::GET)
                    {
                        _msg->result = RESULT::SUCCESS;
                        _msg->content.value = get_temperature();
                    }
                    else if (_msg->content.function == FUNCTION::ALARM)
                    {
                        _msg->result = RESULT::UNSUPPORTED;
                        _msg->content.value = std::numeric_limits<float>::lowest();
                    }
                    else
                    {
                        _msg->result = RESULT::UNKNOWN;
                        _msg->content.value = std::numeric_limits<float>::lowest();
                    }
                }

                /**
                    \brief Send temperature confirmation
                */
                extern void confirmation(message_t *const _msg)
                {
                    assert(_msg != NULL); // command control temperature confirmation message not null

                    /* handle */
                    uint8_t space[CFM_SIZE] = {0};
                    _msg->value.size = CFM_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::TEMPERATURE_CFM;
                    *ptr++ = (uint8_t)_msg->result;

                    _msg->content.serialize(ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }

                /**
                    \brief Send temperature indication
                */
                extern void indication(message_t *const _msg)
                {
                    assert(_msg != NULL); // command control temperature indication message NULL

                    /* handle */
                    uint8_t space[IND_SIZE] = {0};
                    _msg->value.size = IND_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::TEMPERATURE_IND;
                    _msg->content.serialize(ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}