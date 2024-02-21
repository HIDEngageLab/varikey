/**
 * \file cmd_parameter_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Parameter message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "cmd_parameter_msg.hpp"
#include "commander.hpp"
#include "param_backlight.hpp"
#include "param_display.hpp"
#include "param_features.hpp"
#include "param_keypad.hpp"
#include "param_maintainer.hpp"
#include "param_mapping.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_user.hpp"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace param
            {
                static const size_t CFM_SIZE = 4;

                /**
                    \brief De-serialize parameter request
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    assert(_chunk != NULL && _msg != NULL); /* param message chunk null */

                    using FUNCTION = engine::payload::parameter::FUNCTION;
                    using IDENTIFIER = registry::parameter::IDENTIFIER;

                    auto set_message_result = [&](const registry::result_t result)
                    {
                        switch (result)
                        {
                        case registry::result_t::SUCCESS:
                            _msg->result = engine::hci::cmd::param::RESULT::SUCCESS;
                            break;
                        case registry::result_t::FAILURE:
                            _msg->result = engine::hci::cmd::param::RESULT::FAILURE;
                            break;
                        case registry::result_t::ERROR:
                            _msg->result = engine::hci::cmd::param::RESULT::ERROR;
                            break;
                        default:
                            _msg->result = engine::hci::cmd::param::RESULT::UNKNOWN;
                            break;
                        }
                    };

                    /* deserialize */
                    _msg->content.deserialize(_chunk->space);
                    if (_msg->content.identifier != IDENTIFIER::UNDEFINED)
                    {
                        if (_msg->content.function == FUNCTION::SET)
                        {
                            const registry::result_t result = engine::payload::parameter::set_parameter(_msg->content);
                            set_message_result(result);
                        }
                        else if (_msg->content.function == FUNCTION::GET)
                        {
                            const registry::result_t result = engine::payload::parameter::get_parameter(_msg->content);
                            set_message_result(result);
                        }
                        else
                        {
                            _msg->content.function = FUNCTION::UNDEFINED;
                            _msg->result = RESULT::UNKNOWN;
                        }
                    }
                    else
                    {
                        _msg->result = RESULT::UNKNOWN;
                    }
                }

                /**
                    \brief Serialize and send parameter confirmation
                */
                extern void confirmation(message_t *const _msg)
                {
                    assert(_msg != NULL); /* param message null */

                    /* serialize */
                    const uint8_t MESSAGE_LENGTH = CFM_SIZE + _msg->value.size;
                    uint8_t space[MESSAGE_LENGTH];
                    _msg->value.space = space;
                    _msg->value.size = CFM_SIZE;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::PARAM_CFM;
                    *ptr++ = (uint8_t)_msg->result;

                    _msg->content.serialize(ptr);
                    _msg->value.size += _msg->content.size();

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}
