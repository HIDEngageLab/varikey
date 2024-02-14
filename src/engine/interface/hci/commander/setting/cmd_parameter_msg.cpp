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
                    if (_msg->content.identifier == IDENTIFIER::UNDEFINED)
                    {
                        _msg->result = RESULT::UNKNOWN;
                    }
                    if (!(_msg->content.function == FUNCTION::GET ||
                          _msg->content.function == FUNCTION::SET))
                    {
                        _msg->result = RESULT::UNKNOWN;
                    }

                    if (_msg->result != RESULT::UNKNOWN)
                    {
                        const chunk_t parameter_space{.space = (uint8_t *const)&_chunk->space[2],
                                                      .size = registry::parameter::backlight::SIZE};
                        registry::result_t result;

                        if (_msg->content.function == FUNCTION::SET)
                        {
                            switch (_msg->content.identifier)
                            {
                            case IDENTIFIER::BACKLIGHT:
                                result = registry::backlight_set(&parameter_space);
                                break;
                            case IDENTIFIER::DISPLAY:
                                result = registry::display_set(&parameter_space);
                                break;
                            case IDENTIFIER::FEATURES:
                                result = registry::features_set(&parameter_space);
                                break;
                            case IDENTIFIER::KEYPAD:
                                result = registry::keypad_set(&parameter_space);
                                break;
                            case IDENTIFIER::MAINTAINER:
                                result = registry::maintainer_set(&parameter_space);
                                break;
                            case IDENTIFIER::MAPPING:
                                result = registry::mapping_set(&parameter_space);
                                break;
                            case IDENTIFIER::POSITION:
                                result = registry::position_set(&parameter_space);
                                break;
                            case IDENTIFIER::SERIAL_NUMBER:
                                result = registry::serial_number_set(&parameter_space);
                                break;
                            case IDENTIFIER::USER:
                                result = registry::user_set(&parameter_space);
                                break;

                            default:
                                _msg->result = engine::hci::cmd::param::RESULT::UNKNOWN;
                                break;
                            }

                            set_message_result(result);
                        }
                        else if (_msg->content.function == FUNCTION::GET)
                        {
                            using IDENTIFIER = registry::parameter::IDENTIFIER;

                            auto handle_backlight_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::backlight_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::backlight::register_t);
                            };

                            auto handle_display_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::display_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::display::register_t);
                            };

                            auto handle_feature_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::features_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::features::register_t);
                            };

                            auto handle_keypad_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::keypad_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::keypad::register_t);
                            };

                            auto handle_maintainer_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::maintainer_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::maintainer::register_t);
                            };

                            auto handle_mapping_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::mapping_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::mapping::register_t);
                            };

                            auto handle_position_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::position_get(&_msg->value));
                                _msg->value.size = sizeof(registry::parameter::position::register_t);
                            };

                            auto handle_serial_number_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::serial_number_get(&_msg->value));
                                _msg->value.size = registry::parameter::serial_number::SIZE;
                            };

                            auto handle_user_request = [&]()
                            {
                                _msg->result = static_cast<const param::RESULT>(registry::user_get(&_msg->value));
                                _msg->value.size = registry::parameter::user::SIZE;
                            };

                            switch (_msg->content.identifier)
                            {
                            case IDENTIFIER::BACKLIGHT:
                                handle_backlight_request();
                                break;
                            case IDENTIFIER::DISPLAY:
                                handle_display_request();
                                break;
                            case IDENTIFIER::FEATURES:
                                handle_feature_request();
                                break;
                            case IDENTIFIER::KEYPAD:
                                handle_keypad_request();
                                break;
                            case IDENTIFIER::MAINTAINER:
                                handle_maintainer_request();
                                break;
                            case IDENTIFIER::MAPPING:
                                handle_mapping_request();
                                break;
                            case IDENTIFIER::POSITION:
                                handle_position_request();
                                break;
                            case IDENTIFIER::SERIAL_NUMBER:
                                handle_serial_number_request();
                                break;
                            case IDENTIFIER::USER:
                                handle_user_request();
                                break;

                            default:
                                _msg->result = engine::hci::cmd::param::RESULT::UNKNOWN;
                                break;
                            }
                            set_message_result(result);
                        }
                        else
                        {
                            _msg->content.function = FUNCTION::UNDEFINED;
                        }
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
