/**
 * \file serial_msg.cpp
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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "serial_msg.hpp"

namespace engine
{
    namespace serial
    {
        namespace msg
        {
            /**
                \brief Serialize serial engine message
            */
            extern void serialize(unit_t const *const _msg, chunk_t *const _chunk)
            {
                assert(_msg != NULL && _chunk != NULL); /* serial message null */
                uint8_t *cursor = _chunk->space;

                switch (_msg->type)
                {
                case TYPE::COMMANDER:
                    *cursor++ = static_cast<uint8_t>(TYPE::COMMANDER);
                    break;

                case TYPE::MONITORING:
                    *cursor++ = static_cast<uint8_t>(TYPE::MONITORING);
                    break;

                default:
                    assert(false); /* wrong serial message type */
                }

                assert(_msg->payload->size <= _chunk->size - 1); /* serial frame parser: chunk size */
                uint8_t *msg_ptr = _msg->payload->space;

                for (uint8_t i = 0; i < _msg->payload->size; ++i)
                {
                    *cursor++ = *msg_ptr++;
                }
            }

            /**
                \brief De-Serialize serial engine message
            */
            extern void deserialize(unit_t *const _msg, chunk_t const *const _chunk)
            {
                assert(_msg != NULL && _chunk != NULL); /* serial message null */
                uint8_t const *cursor = _chunk->space;

                const TYPE msg_type = static_cast<const TYPE>(*cursor++);
                switch (msg_type)
                {
                case TYPE::COMMANDER:
                    _msg->type = TYPE::COMMANDER;
                    break;

                case TYPE::MONITORING:
                    _msg->type = TYPE::MONITORING;
                    break;

                default:
                    assert(false); /* wrong serial message type */
                }

                assert(_msg->payload->size <= _chunk->size - 1); /* serial frame parser: chunk size */
                uint8_t *msg_ptr = _msg->payload->space;

                for (uint8_t i = 0; i < _msg->payload->size; ++i)
                {
                    *msg_ptr++ = *cursor++;
                }
            }
        }
    }
}
