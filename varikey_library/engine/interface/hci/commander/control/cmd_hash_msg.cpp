// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd hash msg module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "checksum.hpp"
#include "cmd_hash_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine::hci::cmd::hash
{
    static const size_t CFM_SIZE = 4;

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {

        assert(_chunk != NULL && _msg != NULL);

        _msg->result = RESULT::SUCCESS;
        _msg->hash = checksum_crc(_chunk, 0);

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

        *ptr++ = (uint8_t)engine::hci::COMMAND::HASH_CFM;
        *ptr++ = (uint8_t)_msg->result;
        serialize_word(_msg->hash, &ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}