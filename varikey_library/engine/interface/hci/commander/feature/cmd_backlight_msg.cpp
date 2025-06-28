/**
 * \file cmd_backlight_msg.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <cstdlib>

#include "backlight3.hpp"
#include "cmd_backlight_msg.hpp"
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
            namespace backlight
            {
                static const size_t CFM_SIZE = 6;

                /**
                 * \brief Backlight message request
                 *
                 * \param _chunk
                 * \param _msg
                 */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    /* checks */
                    assert(_chunk != NULL && _msg != NULL); /* request chunk null */

                    /* deserialize */
                    _msg->result = RESULT::SUCCESS;

                    _msg->content.deserialize(_chunk->space);

                    switch (_msg->content.program)
                    {
                    case engine::backlight::PROGRAM::ALERT:
                        engine::backlight::set_program(engine::backlight::PROGRAM::ALERT, 0);
                        break;
                    case engine::backlight::PROGRAM::CONST:
                        engine::backlight::set_program(engine::backlight::PROGRAM::CONST, 0);
                        break;
                    case engine::backlight::PROGRAM::MEDIUM:
                        engine::backlight::set_program(engine::backlight::PROGRAM::MEDIUM, 0);
                        break;
                    case engine::backlight::PROGRAM::MORPH:
                        engine::backlight::set_program(engine::backlight::PROGRAM::CONST, 0);
                        engine::backlight::morph_left(_msg->content.left);
                        engine::backlight::morph_right(_msg->content.right);
                        break;
                    case engine::backlight::PROGRAM::MOUNT:
                        engine::backlight::set_program(engine::backlight::PROGRAM::MOUNT, 0);
                        break;
                    case engine::backlight::PROGRAM::OFF:
                        engine::backlight::set_program(engine::backlight::PROGRAM::OFF, 0);
                        break;
                    case engine::backlight::PROGRAM::SET:
                        engine::backlight::set_program(engine::backlight::PROGRAM::CONST, 0);
                        engine::backlight::set_left(_msg->content.left);
                        engine::backlight::set_right(_msg->content.right);
                        break;
                    case engine::backlight::PROGRAM::SLOW:
                        engine::backlight::set_program(engine::backlight::PROGRAM::SLOW, 0);
                        break;
                    case engine::backlight::PROGRAM::SUSPEND:
                        engine::backlight::set_program(engine::backlight::PROGRAM::SUSPEND, 0);
                        break;
                    case engine::backlight::PROGRAM::TURBO:
                        engine::backlight::set_program(engine::backlight::PROGRAM::TURBO, 0);
                        break;
                    default:
                        engine::backlight::set_program(engine::backlight::PROGRAM::MEDIUM, 0);
                        _msg->result = RESULT::WRONG_MODE;
                        break;
                    }
                    _msg->value.size = 0;
                    _msg->value.space = 0;
                }

                /**
                 * \brief Backlight confirmation message send
                 *
                 * \param _msg
                 */
                extern void confirmation(message_t *const _msg)
                {
                    /* checks */
                    assert(_msg != NULL); /* confirmation message null */

                    /* handle */
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
        }
    }
}
