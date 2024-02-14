/**
 * \file cmd_hash_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Key message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_HASH_MSG_HPP__
#define __CMD_HASH_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace hash
            {
                /** \brief Key message result code */
                enum class RESULT : uint8_t
                {
                    SUCCESS = common::result::SUCCESS,
                    FAILURE = common::result::FAILURE,
                };

                /**
                    \brief Store req/cfm message
                */
                struct message_t
                {
                    RESULT result;
                    uint32_t hash;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
            }
        }
    }
}

#endif /* __CMD_HASH_MSG_HPP__ */
