/**
 * \file cmd_display_msg.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <cstdlib>

#include "cmd_display_msg.hpp"
#include "commander.hpp"
#include "display.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace display
            {
                static const size_t CFM_SIZE = 2;
                static const size_t MAX_CFM_SIZE = 5;

                /**
                 * \brief Display message request
                 *
                 * \param _chunk
                 * \param _msg
                 */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    using FUNCTION = engine::payload::display::FUNCTION;
                    /* checks */
                    assert(_chunk != NULL && _msg != NULL); /* request chunk null */

                    /* deserialize */
                    _msg->result = RESULT::SUCCESS;
                    _chunk->space[_chunk->size] = 0;
                    _msg->content.deserialize(_chunk->space);

                    switch (_msg->content.function)
                    {
                    case FUNCTION::CLEAN:
                        engine::display::clean();
                        break;
                    case FUNCTION::FONT:
                        if (engine::display::font::is_defined(_msg->content.font))
                        {
                            engine::display::set_font(_msg->content.font);
                        }
                        else
                        {
                            engine::display::set_font(engine::display::FONT::SMALL);
                            _msg->result = RESULT::UNKNOWN;
                        }
                        break;
                    case FUNCTION::ICON:
                        if (engine::display::image::is_defined(_msg->content.icon))
                        {
                            engine::display::draw(_msg->content.icon);
                        }
                        else
                        {
                            engine::display::draw(engine::display::ICON::VARIKEY_LOGO);
                            _msg->result = RESULT::UNKNOWN;
                        }
                        break;
                    case FUNCTION::POSITION:
                        engine::display::set_cursor(_msg->content.position.line,
                                                    _msg->content.position.column);

                        break;
                    case FUNCTION::TEXT:
                    {
                        engine::display::print(_msg->content.text);
                        break;
                    }
                    default:
                        _msg->result = RESULT::UNKNOWN;
                        break;
                    }

                    _msg->value.size = 0;
                    _msg->value.space = 0;
                }

                /**
                 * \brief display confirmation message send
                 *
                 * \param _msg
                 */
                extern void confirmation(message_t *const _msg)
                {
                    /* checks */
                    assert(_msg != NULL); /* confirmation message null */

                    /* handle */
                    uint8_t space[MAX_CFM_SIZE] = {0};
                    _msg->value.size = CFM_SIZE + _msg->content.size();
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::DISPLAY_CFM;
                    *ptr++ = (uint8_t)_msg->result;
                    _msg->content.serialize(&ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}
