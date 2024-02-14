/**
 * \file cmd_parameter_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Parameter message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_PARAM_PARAMETER_MSG_HPP__
#define __CMD_PARAM_PARAMETER_MSG_HPP__

#include <stdint.h>

#include "chunk.h"
#include "macros.hpp"
#include "parameter.hpp"
#include "payload_parameter.hpp"
namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace param
            {
                /** \brief Parameter request result type */
                enum class RESULT : uint8_t
                {
                    ERROR = common::result::ERROR,
                    FAILURE = common::result::FAILURE,
                    SUCCESS = common::result::SUCCESS,
                    UNKNOWN = common::result::UNKNOWN,
                    UNSUPPORTED = common::result::UNSUPPORTED,
                };

                /** \brief Parameter message */
                struct message_t
                {
                    RESULT result;
                    payload::parameter::content_t content;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void confirmation(message_t *const _msg);
            }
        }
    }
}

#endif /* __CMD_PARAM_PARAMETER_MSG_HPP__ */
