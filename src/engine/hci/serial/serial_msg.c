/**
 * \file serial_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Message over serial interface

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>

#include "serial_msg.h"

/**
    \brief Serialize serial engine message
*/
extern void serial_msg_serialize(serial_msg_t const *const _msg, chunk_t *const _chunk)
{
    /* checks */
    assert(_msg != NULL && _chunk != NULL); /* serial message null */
    uint8_t *cursor = _chunk->space;

    switch (_msg->type)
    {
    case SERIAL_MSG_TYPE_COMMANDER:
        *cursor++ = SERIAL_MSG_TYPE_COMMANDER;
        break;

    case SERIAL_MSG_TYPE_MONITORING:
        *cursor++ = SERIAL_MSG_TYPE_MONITORING;
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
extern void serial_msg_deserialize(serial_msg_t *const _msg, chunk_t const *const _chunk)
{
    /* checks */
    assert(_msg != NULL && _chunk != NULL); /* serial message null */
    uint8_t const *cursor = _chunk->space;

    switch (*cursor++)
    {
    case SERIAL_MSG_TYPE_COMMANDER:
        _msg->type = SERIAL_MSG_TYPE_COMMANDER;
        break;

    case SERIAL_MSG_TYPE_MONITORING:
        _msg->type = SERIAL_MSG_TYPE_MONITORING;
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
