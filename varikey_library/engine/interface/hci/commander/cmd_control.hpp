/**
 * \file cmd_control.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module control

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_CONTROL_HPP__
#define __CMD_CONTROL_HPP__

#include "chunk.h"
#include "cmd_reset_msg.hpp"
#include "engine_defines.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace control
            {
                extern void gadget_indication(engine::defines::STATE const);
                extern void gadget_request(chunk_t const *const);
                extern void hash_request(chunk_t const *const);
                extern void reset_indication(hci::cmd::reset::RESULT const);
                extern void reset_request(chunk_t const *const);
                extern void temperature_request(chunk_t const *const);
            }
        }
    }
}

#endif /* __CMD_CONTROL_HPP__ */
