/**
 * \file payload_gpio.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PAYLOAD_GPIO_HPP__
#define __PAYLOAD_GPIO_HPP__

#include <cstdint>
#include <cstdlib>

#include "board_defines.hpp"
#include "macros.hpp"
#include "payload_identifier.hpp"

namespace engine
{
    namespace payload
    {
        namespace gpio
        {
            using IDENTIFIER = platform::board::IDENTIFIER;

            /** \brief GPIO message direction code */
            using DIRECTION = platform::board::DIRECTION;

            /** \brief GPIO message level code */
            using VALUE = platform::board::VALUE;

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

            struct content_t
            {
                FUNCTION function;
                IDENTIFIER identifier;
                uint32_t diff;

                static const size_t size() { return 2; }
                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };
        }
    }
}

#endif // __PAYLOAD_GPIO_HPP__
