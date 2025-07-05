// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd backlight msg module
// SPDX-FileType: SOURCE

#include <cassert>
#include <cstdlib>

#include "backlight.hpp"
#include "cmd_backlight_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine::hci::cmd::backlight
{
    static const size_t CFM_SIZE = 6;

    extern void request(chunk_t const *const _chunk, message_t *const _msg)
    {

        assert(_chunk != NULL && _msg != NULL);

        _msg->result = RESULT::SUCCESS;
        _msg->content.deserialize(_chunk->space);

        if (_msg->content.program == engine::backlight::PROGRAM::MORPH ||
            _msg->content.program == engine::backlight::PROGRAM::SET)
        {
            engine::backlight::set_program(engine::backlight::PROGRAM::CONST,
                                           _msg->content.channel,
                                           _msg->content.left,
                                           _msg->content.right,
                                           0);
        }
        else if (_msg->content.program == engine::backlight::PROGRAM::ALERT ||
                 _msg->content.program == engine::backlight::PROGRAM::SLOW ||
                 _msg->content.program == engine::backlight::PROGRAM::TURBO ||
                 _msg->content.program == engine::backlight::PROGRAM::MEDIUM ||
                 _msg->content.program == engine::backlight::PROGRAM::SUSPEND ||
                 _msg->content.program == engine::backlight::PROGRAM::MOUNT ||
                 _msg->content.program == engine::backlight::PROGRAM::OFF)
        {
            engine::backlight::set_program(_msg->content.program,
                                           _msg->content.channel,
                                           0);
        }
        else
        {
            engine::backlight::set_program(engine::backlight::PROGRAM::MEDIUM,
                                           _msg->content.channel,
                                           0);
            _msg->result = RESULT::WRONG_MODE;
        }

        _msg->value.size = 0;
        _msg->value.space = 0;
    }

    extern void confirmation(message_t *const _msg)
    {

        assert(_msg != NULL);

        uint8_t space[CFM_SIZE] = {0};
        _msg->value.space = space;
        _msg->value.size = 2 + _msg->content.size();
        uint8_t *ptr = space;

        *ptr++ = (uint8_t)engine::hci::COMMAND::BACKLIGHT_CFM;
        *ptr++ = (uint8_t)_msg->result;

        _msg->content.serialize(&ptr);

        serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
    }
}