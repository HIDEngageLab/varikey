/**
 * \file cmd_gpio_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief GPIO message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_GPIO_MSG_HPP__
#define __CMD_GPIO_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

#include "payload_gpio.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace gpio
            {
                using content_t = engine::payload::gpio::content_t;

                /** \brief GPIO message result code */
                enum class RESULT : uint8_t
                {
                    FAILURE = common::result::FAILURE,
                    SUCCESS = common::result::SUCCESS,
                    UNKNOWN = common::result::UNKNOWN,
                    UNSUPPORTED = common::result::UNSUPPORTED,

                    WRONG_DIRECTION = common::result::CUSTOM + 0,
                    WRONG_IDENTIFIER = common::result::CUSTOM + 1,
                };

                /** \brief GPIO message */
                struct message_t
                {
                    RESULT result;
                    content_t content;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
                extern void indication(message_t *const _msg);
            }
        }
    }
}

#endif /* __CMD_GPIO_MSG_HPP__ */
