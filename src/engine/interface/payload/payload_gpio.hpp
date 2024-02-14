/**
 * \file payload_gpio.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_GPIO_HPP__
#define __PAYLOAD_GPIO_HPP__

#include <stdint.h>

#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace gpio
        {
            const uint8_t GPIO_ID = to_underlying(payload::IDENTIFIER::GPIO);

            /** \brief GPIO message function */
            enum class FUNCTION : uint8_t
            {
                DISABLE = common::function::DISABLE,
                ENABLE = common::function::ENABLE,

                DIRECTION_GET = common::function::CUSTOM,
                DIRECTION_SET = common::function::CUSTOM + 1,
                LEVEL_GET = common::function::CUSTOM + 4,
                LEVEL_SET = common::function::CUSTOM + 5,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            enum class IDENTIFIER : uint8_t
            {
                PIN1 = GPIO_ID + 0x0a,
                PIN2 = GPIO_ID + 0x0b,
                PIN3 = GPIO_ID + 0x0c,
                PIN4 = GPIO_ID + 0x0d,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            /** \brief GPIO message direction code */
            enum class DIRECTION : uint8_t
            {
                INPUT = 0x00,
                OUTPUT = 0x01,
                UNDEFINED = 0xFF,
            };

            /** \brief GPIO message level code */
            enum class LEVEL : uint8_t
            {
                LOW = 0x00,
                HIGH = 0x01,
                UNDEFINED = 0xff,
            };

            struct __attribute__((packed)) content_t
            {
                static const size_t CFM_SIZE = 4;

                FUNCTION function;
                IDENTIFIER identifier;
                DIRECTION direction;
                LEVEL level;

                static const size_t size() { return CFM_SIZE; }

                void deserialize(uint8_t const *const _space)
                {
                    function = static_cast<FUNCTION>(_space[0]);
                    if (!(function == FUNCTION::DISABLE ||
                          function == FUNCTION::ENABLE ||
                          function == FUNCTION::DIRECTION_GET ||
                          function == FUNCTION::DIRECTION_SET ||
                          function == FUNCTION::LEVEL_GET ||
                          function == FUNCTION::LEVEL_SET))
                    {
                        function = FUNCTION::UNDEFINED;
                    }

                    identifier = static_cast<const IDENTIFIER>(_space[1]);
                    if (!(identifier == IDENTIFIER::PIN1 ||
                          identifier == IDENTIFIER::PIN2 ||
                          identifier == IDENTIFIER::PIN3 ||
                          identifier == IDENTIFIER::PIN4))
                    {
                        identifier = IDENTIFIER::UNDEFINED;
                    }

                    if (function == FUNCTION::DIRECTION_SET)
                    {
                        direction = static_cast<DIRECTION>(_space[2]);
                        if (!(direction == DIRECTION::INPUT ||
                              direction == DIRECTION::OUTPUT))
                        {
                            direction = DIRECTION::UNDEFINED;
                        }
                    }
                    else if (function == FUNCTION::LEVEL_SET)
                    {
                        level = static_cast<const LEVEL>(_space[2]);
                        if (level == LEVEL::LOW ||
                            level == LEVEL::HIGH)
                        {
                            level = LEVEL::UNDEFINED;
                        }
                    }
                }

                void serialize(uint8_t *const _space)
                {
                    uint8_t *ptr = _space;
                    *ptr++ = (uint8_t)identifier;
                    *ptr++ = (uint8_t)function;
                    if (function == FUNCTION::DIRECTION_SET)
                    {
                        *ptr++ = (uint8_t)direction;
                    }
                    else if (function == FUNCTION::LEVEL_SET)
                    {
                        *ptr++ = (uint8_t)level;
                    }
                }
            };
        }
    }
}

#endif // __PAYLOAD_GPIO_HPP__
