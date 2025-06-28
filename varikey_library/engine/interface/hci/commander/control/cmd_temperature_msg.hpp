/**
 * \file cmd_temperature_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Temperature message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_TEMPERATURE_MSG_HPP__
#define __CMD_TEMPERATURE_MSG_HPP__

#include "macros.hpp"
#include "payload_temperature.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace temperature
            {
                using content_t = engine::payload::temperature::content_t;

                /** \brief Temperature message result code */
                enum class RESULT : uint8_t
                {
                    SUCCESS = common::result::SUCCESS,
                    FAILURE = common::result::FAILURE,
                    UNSUPPORTED = common::result::UNSUPPORTED,
                    UNKNOWN = common::result::UNKNOWN,
                };

                /** \brief Temperature message */
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

#endif /*  __CMD_TEMPERATURE_MSG_HPP__ */
