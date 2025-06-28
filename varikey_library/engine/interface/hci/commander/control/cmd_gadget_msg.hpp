/**
 * \file cmd_gadget_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief status message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_GADGET_MSG_HPP__
#define __CMD_GADGET_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"
#include "payload_gadget.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace gadget
            {
                using content_t = payload::gadget::content_t;

                /** \brief Status message result code */
                enum class RESULT : uint8_t
                {
                    FAILURE = common::result::FAILURE,
                    SUCCESS = common::result::SUCCESS,
                    UNKNOWN = common::result::UNKNOWN,
                    UNSUPPORTED = common::result::UNSUPPORTED,

                    WRONG_STATE = common::result::CUSTOM,
                };

                /** \brief Status message */
                struct message_t
                {
                    RESULT result;
                    content_t gadget;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
                extern void indication(message_t *const _msg);
            }
        }
    }
}

#endif /*  __CMD_GADGET_MSG_HPP__ */
