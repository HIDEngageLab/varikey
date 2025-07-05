// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd gpio msg module
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "cmd_feature.hpp"
#include "cmd_gpio_msg.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"

namespace engine::hci::cmd::gpio
{
    static const size_t CFM_SIZE = 6;
    static const size_t IND_SIZE = 7;

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {
        assert(_chunk != NULL && _msg != NULL); // chunk is not null

        _msg->content.deserialize(_chunk->space);

        _msg->value.size = 0;
        _msg->value.space = 0;
    }

    extern void confirmation(message_t *const _msg)
    {
        assert(_msg != NULL); // command target GPIO confirmation message not null

        uint8_t space[CFM_SIZE] = {0};
        _msg->value.size = CFM_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::GPIO_CFM;
        *ptr++ = (uint8_t)_msg->result;

        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }

    extern void indication(message_t *const _msg)
    {
        assert(_msg != NULL); // command target GPIO indication message not null

        uint8_t space[IND_SIZE] = {0};
        _msg->value.size = IND_SIZE;
        _msg->value.space = space;
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::GPIO_IND;

        _msg->content.serialize(&ptr);

        serialize_long(_msg->content.diff, &ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}