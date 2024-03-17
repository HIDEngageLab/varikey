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
            /** \brief GPIO message function */
            enum class FUNCTION : uint8_t
            {
                DISABLE = common::function::DISABLE,
                ENABLE = common::function::ENABLE,

                DIRECTION = common::function::CUSTOM,
                IN = common::function::CUSTOM + 1,
                OUT = common::function::CUSTOM + 2,
                VALUE = common::function::CUSTOM + 3,
                HIGH = common::function::CUSTOM + 4,
                LOW = common::function::CUSTOM + 5,

                UNDEFINED = to_underlying(payload::IDENTIFIER::UNDEFINED),
            };

            using IDENTIFIER = platform::board::IDENTIFIER;

            /** \brief GPIO message direction code */
            using DIRECTION = platform::board::DIRECTION;

            /** \brief GPIO message level code */
            using VALUE = platform::board::VALUE;

            struct __attribute__((packed)) content_t
            {
                FUNCTION function;
                IDENTIFIER identifier;
                uint32_t diff;

                static const size_t size() { return 2; }

                void deserialize(uint8_t const *const _space)
                {
                    function = static_cast<FUNCTION>(_space[0]);
                    if (!(function == FUNCTION::DISABLE ||
                          function == FUNCTION::ENABLE ||
                          function == FUNCTION::DIRECTION ||
                          function == FUNCTION::IN ||
                          function == FUNCTION::OUT ||
                          function == FUNCTION::VALUE ||
                          function == FUNCTION::HIGH ||
                          function == FUNCTION::LOW))
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
                }

                void serialize(uint8_t **_ptr) const
                {
                    *(*_ptr)++ = (uint8_t)function;
                    *(*_ptr)++ = (uint8_t)identifier;
                }
            };
        }
    }
}

#endif // __PAYLOAD_GPIO_HPP__
