/**
 * \file serial_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Message over serial interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __SERIAL_MSG_HPP__
#define __SERIAL_MSG_HPP__

#include <stdint.h>

#include "chunk.h"

namespace engine
{
    /** \brief Internal serial message type */
    namespace serial
    {
        namespace msg
        {
            enum class TYPE : uint8_t
            {
                COMMANDER = 0x01,
                MONITORING = 0x02,
            };

            /** \brief Serial message */
            struct unit_t
            {
                TYPE type;        /**< Internal type for command interpreter */
                chunk_t *payload; /**< \brief Entails command field and command data */
            };

            extern void serialize(unit_t const *const _msg, chunk_t *const _chunk);
            extern void deserialize(unit_t *const _msg, chunk_t const *const _chunk);
        }
    }
}

#endif /* __SERIAL_MSG_HPP__ */
