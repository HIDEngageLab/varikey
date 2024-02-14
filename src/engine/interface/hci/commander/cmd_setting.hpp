/**
 * \file cmd_setting.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module configuration

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_SETTING_HPP__
#define __CMD_SETTING_HPP__

#include "chunk.h"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace setting
            {
                extern void identifier_request(chunk_t const *_chunk);
                extern void parameter_request(chunk_t const *_chunk);
            }
        }
    }
}

#endif /* __CMD_SETTING_HPP__ */
