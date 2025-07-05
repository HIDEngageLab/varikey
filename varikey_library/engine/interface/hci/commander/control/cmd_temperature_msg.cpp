// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd temperature msg module
// SPDX-FileType: SOURCE

#include <limits>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "board_assembly.hpp"
#include "chunk.h"
#include "cmd_temperature_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "serial_frame.hpp"

namespace engine::hci::cmd::temperature
{
    static const size_t CFM_SIZE = 7;
    static const size_t IND_SIZE = 5;

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {
        (void)_chunk;
        assert(_msg != NULL); // message is not null

        using FUNCTION = engine::payload::temperature::FUNCTION;

        _msg->content.deserialize(_chunk->space);
        if (_msg->content.function == FUNCTION::GET)
        {
            _msg->result = RESULT::SUCCESS;
            _msg->content.value = platform::board::assembly.soc.get_temperature();
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

    extern void confirmation(message_t *const _msg)
    {
        assert(_msg != NULL); // command control temperature confirmation message not null

        uint8_t space[CFM_SIZE] = {0};
        _msg->value.size = CFM_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::TEMPERATURE_CFM;
        *ptr++ = (uint8_t)_msg->result;

        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }

    extern void indication(message_t *const _msg)
    {
        assert(_msg != NULL); // command control temperature indication message NULL

        uint8_t space[IND_SIZE] = {0};
        _msg->value.size = IND_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::TEMPERATURE_IND;
        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}