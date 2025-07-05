// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd protocol msg module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "cmd_protocol_msg.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"

namespace engine::hci::cmd::protocol
{
    static const size_t IND_SIZE = 2;
    static const size_t BUFFER_SIZE = 64;

    extern void indication(message_t *const _msg, chunk_t const *const _chunk)
    {
        assert(_msg != NULL); // command control hci_status indication message not null

        uint8_t space[IND_SIZE + BUFFER_SIZE] = {0};
        _msg->value.size = IND_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::PROTOCOL_IND;
        *ptr++ = (uint8_t)_msg->result;
        for (size_t i = 0; i < _chunk->size && i < BUFFER_SIZE; ++i)
        {
            *ptr++ = _chunk->space[i];
            _msg->value.size++;
        }

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}
