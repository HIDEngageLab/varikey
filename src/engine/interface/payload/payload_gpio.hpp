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

#include "board_defines.hpp"
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

            using IDENTIFIER = platform::board::IDENTIFIER;

            /** \brief GPIO message direction code */
            using DIRECTION = platform::board::DIRECTION;

            /** \brief GPIO message level code */
            using LEVEL = platform::board::VALUE;

            struct __attribute__((packed)) content_t
            {
                FUNCTION function;
                IDENTIFIER identifier;
                union
                {
                    DIRECTION direction;
                    LEVEL level;
                };

                static const size_t size() { return 3; }

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
                    if (!(identifier == IDENTIFIER::GPIO0 ||
                          identifier == IDENTIFIER::GPIO1 ||
                          identifier == IDENTIFIER::GPIO2 ||
                          identifier == IDENTIFIER::GPIO3))
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

                void serialize(uint8_t *const _space) const
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
