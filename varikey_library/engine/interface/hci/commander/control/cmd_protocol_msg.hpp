/**
 * \file cmd_protocol_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief HCI status message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_PROTOCOL_MSG_HPP__
#define __CMD_PROTOCOL_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace protocol
            {
                /** \brief Status message result code */
                enum class RESULT : uint8_t
                {
                    FAILURE = common::result::FAILURE,
                    SUCCESS = common::result::SUCCESS,
                    UNSUPPORTED = common::result::UNSUPPORTED,
                    INVALID_COMMAND = common::result::CUSTOM,
                };

                /** \brief Status message */
                struct message_t
                {
                    RESULT result;
                    chunk_t value;
                };

                extern void indication(message_t *const _msg, chunk_t const *const _chunk);
            }
        }
    }
}

#endif /* __CMD_PROTOCOL_MSG_HPP__ */
