/**
 * \file payload_parameter.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_parameter.hpp"

namespace engine
{
    namespace payload
    {
        namespace parameter
        {
            /**
             * \brief Get payload size
             *
             * \return const size_t
             */
            const size_t content_t::size() const
            {
                size_t payload_size = 2;
                switch (identifier)
                {
                case IDENTIFIER::BACKLIGHT:
                    payload_size += registry::parameter::backlight::SIZE;
                    break;
                case IDENTIFIER::DISPLAY:
                    payload_size += registry::parameter::display::SIZE;
                    break;
                case IDENTIFIER::FEATURES:
                    payload_size += registry::parameter::features::SIZE;
                    break;
                case IDENTIFIER::KEYPAD:
                    payload_size += registry::parameter::keypad::SIZE;
                    break;
                case IDENTIFIER::MAINTAINER:
                    payload_size += registry::parameter::maintainer::SIZE;
                    break;
                case IDENTIFIER::MAPPING:
                    payload_size += registry::parameter::mapping::SIZE;
                    break;
                case IDENTIFIER::POSITION:
                    payload_size += registry::parameter::position::SIZE;
                    break;
                case IDENTIFIER::SERIAL_NUMBER:
                    payload_size += registry::parameter::serial_number::SIZE;
                    break;
                case IDENTIFIER::USER:
                    payload_size += registry::parameter::user::SIZE;
                    break;
                default:
                    break;
                }
                return payload_size;
            }

            /**
             * \brief Deserialize parameter value
             *
             * \param _space
             */
            void content_t::deserialize(uint8_t const *const _space)
            {
                identifier = registry::parameter::to_identifier(_space[0]);
                function = static_cast<FUNCTION>(_space[1]);

                if (function == FUNCTION::SET)
                {
                    switch (identifier)
                    {
                    case IDENTIFIER::BACKLIGHT:
                        parameter.backlight.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::DISPLAY:
                        parameter.display.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::FEATURES:
                        parameter.features.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::KEYPAD:
                        parameter.keypad.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::MAINTAINER:
                        parameter.maintainer.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::MAPPING:
                        parameter.mapping.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::POSITION:
                        parameter.position.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::SERIAL_NUMBER:
                        parameter.serial_number.deserialize(&_space[2]);
                        break;
                    case IDENTIFIER::USER:
                        parameter.user.deserialize(&_space[2]);
                        break;
                    default:
                        break;
                    }
                }
            }

            /**
             * \brief Serialize parameter value
             *
             * \param _space
             */
            void content_t::serialize(uint8_t **_ptr) const
            {
                *(*_ptr)++ = (uint8_t)identifier;
                *(*_ptr)++ = (uint8_t)function;

                switch (identifier)
                {
                case IDENTIFIER::BACKLIGHT:
                    parameter.backlight.serialize(_ptr);
                    break;
                case IDENTIFIER::DISPLAY:
                    parameter.display.serialize(_ptr);
                    break;
                case IDENTIFIER::FEATURES:
                    parameter.features.serialize(_ptr);
                    break;
                case IDENTIFIER::KEYPAD:
                    parameter.keypad.serialize(_ptr);
                    break;
                case IDENTIFIER::MAINTAINER:
                    parameter.maintainer.serialize(_ptr);
                    break;
                case IDENTIFIER::MAPPING:
                    parameter.mapping.serialize(_ptr);
                    break;
                case IDENTIFIER::POSITION:
                    parameter.position.serialize(_ptr);
                    break;
                case IDENTIFIER::SERIAL_NUMBER:
                    parameter.serial_number.serialize(_ptr);
                    break;
                case IDENTIFIER::USER:
                    parameter.user.serialize(_ptr);
                    break;
                default:
                    break;
                }
            }

            /**
             * \brief Set the parameter object
             *
             * \param _content Parameter payload
             * \return result_t
             */
            extern registry::result_t set_parameter(const engine::payload::parameter::content_t &_content)
            {
                registry::result_t result = registry::result_t::FAILURE;

                switch (_content.identifier)
                {
                case parameter::IDENTIFIER::BACKLIGHT:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.backlight.byte,
                                                        .size = registry::parameter::backlight::SIZE};
                    result = registry::backlight_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::DISPLAY:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.display.byte,
                                                        .size = registry::parameter::display::SIZE};
                    result = registry::display_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::FEATURES:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.features.byte,
                                                        .size = registry::parameter::features::SIZE};

                    result = registry::features_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::KEYPAD:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.keypad.byte,
                                                        .size = registry::parameter::keypad::SIZE};
                    result = registry::keypad_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::MAINTAINER:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.maintainer.byte,
                                                        .size = registry::parameter::maintainer::SIZE};
                    result = registry::maintainer_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::MAPPING:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.mapping.value,
                                                        .size = registry::parameter::mapping::SIZE};
                    result = registry::mapping_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::POSITION:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.position.byte,
                                                        .size = registry::parameter::position::SIZE};
                    result = registry::position_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::SERIAL_NUMBER:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.serial_number.value,
                                                        .size = registry::parameter::serial_number::SIZE};
                    result = registry::serial_number_set(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::USER:
                {
                    const const_chunk_t parameter_space{.space = _content.parameter.user.value,
                                                        .size = registry::parameter::user::SIZE};
                    result = registry::user_set(parameter_space);
                    break;
                }

                default:
                    break;
                }

                return result;
            }

            /**
             * \brief Get the parameter object
             *
             * \param _content Parameter payload
             * \return result_t
             */
            extern registry::result_t get_parameter(engine::payload::parameter::content_t &_content)
            {
                registry::result_t result = registry::result_t::FAILURE;

                switch (_content.identifier)
                {
                case parameter::IDENTIFIER::BACKLIGHT:
                {
                    chunk_t parameter_space{.space = _content.parameter.backlight.byte,
                                            .size = registry::parameter::backlight::SIZE};
                    result = registry::backlight_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::DISPLAY:
                {
                    chunk_t parameter_space{.space = _content.parameter.display.byte,
                                            .size = registry::parameter::display::SIZE};
                    result = registry::display_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::FEATURES:
                {
                    chunk_t parameter_space{.space = _content.parameter.features.byte,
                                            .size = registry::parameter::features::SIZE};
                    result = registry::features_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::KEYPAD:
                {
                    chunk_t parameter_space{.space = _content.parameter.keypad.byte,
                                            .size = registry::parameter::keypad::SIZE};
                    result = registry::keypad_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::MAINTAINER:
                {
                    chunk_t parameter_space{.space = _content.parameter.maintainer.byte,
                                            .size = registry::parameter::maintainer::SIZE};
                    result = registry::maintainer_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::MAPPING:
                {
                    chunk_t parameter_space{.space = _content.parameter.mapping.value,
                                            .size = registry::parameter::mapping::SIZE};
                    result = registry::mapping_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::POSITION:
                {
                    chunk_t parameter_space{.space = _content.parameter.position.byte,
                                            .size = registry::parameter::position::SIZE};
                    result = registry::position_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::SERIAL_NUMBER:
                {
                    chunk_t parameter_space{.space = _content.parameter.serial_number.value,
                                            .size = registry::parameter::serial_number::SIZE};
                    result = registry::serial_number_get(parameter_space);
                    break;
                }
                case parameter::IDENTIFIER::USER:
                {
                    chunk_t parameter_space{.space = _content.parameter.user.value,
                                            .size = registry::parameter::user::SIZE};
                    result = registry::user_get(parameter_space);
                    break;
                }

                default:
                    break;
                }

                return result;
            }
        }
    }
}
