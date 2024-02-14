/**
 * \file cmd_reset_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Reset message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_RESET_MSG_HPP__
#define __CMD_RESET_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"
#include "payload_reset.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace reset
            {
                using content_t = engine::payload::reset::content_t;

                /** \brief Reset message result type */
                enum class RESULT : uint8_t
                {
                    CRITICAL_ERROR = common::result::ERROR, //< initialization failed (hw disabled, safe state)
                    FAILURE = common::result::FAILURE,      //< initialization failed
                    SUCCESS = common::result::SUCCESS,      //< initialization done

                    BACKUP_CREATED = common::result::CUSTOM,          //< no valid maintainer parameter backup
                    PARAMETER_MISSED = common::result::CUSTOM + 1,    //< parameter storage dropped
                    PARAMETER_RECREATED = common::result::CUSTOM + 2, //< parameter storage (re)created, no maintainer parameter backup available (radio disabled)
                    PARAMETER_RESTORED = common::result::CUSTOM + 3,  //< parameter storage (re)created, maintainer parameters restored from backup
                    WATCHDOG = common::result::CUSTOM + 4,            //< reboot after watchdog
                };

                /** \brief Reset message */
                struct message_t
                {
                    RESULT result;
                    content_t content;
                    chunk_t value;
                };

                extern void request(chunk_t const *const _chunk, message_t *const _msg);
                extern void indication(message_t *const _msg);
            }
        }
    }
}

#endif /*  __CMD_RESET_MSG_HPP__ */
