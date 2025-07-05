// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd reset msg module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "chunk.h"
#include "cmd_reset_msg.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"

namespace engine::hci::cmd::reset
{
    static const size_t CFM_SIZE = 2 + sizeof(content_t);
    static const size_t IND_SIZE = 2 + sizeof(content_t);

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {
        (void)_chunk;
        assert(_msg != NULL); // reset request message null

        _msg->result = RESULT::SUCCESS;

        _msg->content.deserialize(_chunk->space);

        _msg->value.size = 0;
        _msg->value.space = 0;
    }

    extern void confirmation(message_t *const _msg)
    {

        assert(_msg != NULL);

        uint8_t space[CFM_SIZE] = {0};
        _msg->value.size = CFM_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::RESET_CFM;
        *ptr++ = (uint8_t)_msg->result;

        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }

    extern void indication(message_t *const _msg)
    {
        assert(_msg != NULL);

        uint8_t space[IND_SIZE] = {0};
        _msg->value.size = IND_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::RESET_IND;
        *ptr++ = (uint8_t)_msg->result;

        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}