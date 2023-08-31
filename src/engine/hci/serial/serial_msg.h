/**
 * \file serial_msg.h
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

#ifndef __SERIAL_MSG_H__
#define __SERIAL_MSG_H__

#include "chunk.h"

/** \brief Internal serial message type */
typedef enum
{
    SERIAL_MSG_TYPE_COMMANDER = 0x01,
    SERIAL_MSG_TYPE_MONITORING = 0x02,
} serial_msg_type_t;

/** \brief Serial message */
typedef struct serial_msg_struct
{
    serial_msg_type_t type; /**< Internal type for command interpreter */
    chunk_t *payload;       /**< \brief Entails command field and command data */
} serial_msg_t;

extern void serial_msg_serialize(serial_msg_t const *const _msg, chunk_t *const _chunk);
extern void serial_msg_deserialize(serial_msg_t *const _msg, chunk_t const *const _chunk);

#endif /* __SERIAL_MSG_H__ */
