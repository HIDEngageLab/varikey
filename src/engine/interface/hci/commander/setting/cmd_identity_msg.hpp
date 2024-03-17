/**
 * \file cmd_identity_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Identifier message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_IDENTITY_MSG_HPP__
#define __CMD_IDENTITY_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"
#include "payload_identity.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace identity
            {
                using content_t = engine::payload::identity::content_t;

                /** \brief Identity request result */
                enum class RESULT : uint8_t
                {
                    FAILURE = common::result::FAILURE,
                    SUCCESS = common::result::SUCCESS,
                    UNKNOWN = common::result::UNKNOWN,
                    UNSUPPORTED = common::result::UNSUPPORTED,
                };

                /** \brief Identity parameter */
                struct message_t
                {
                    content_t identity;
                    RESULT result;

                    chunk_t value;
                };

                extern void request(chunk_t const *_chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
            }
        }
    }
}

#endif /* __CMD_IDENTITY_MSG_HPP__ */
