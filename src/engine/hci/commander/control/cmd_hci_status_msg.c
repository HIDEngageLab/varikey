/**
 * \file cmd_hci_status_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief HCI status message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "chunk.h"
#include "cmd_hci_status_msg.h"
#include "commander.h"
#include "serial_frame.h"

#define PROTOCOL_MESSAGE_IND_SIZE 2
#define PROTOCOL_MESSAGE_IND_BUFFER_SIZE 64

/**
    \brief Send hci_status indication
*/
extern void cmd_hci_status_msg_ind(cmd_hci_status_msg_t *const _msg, chunk_t const *const _chunk)
{
    /* checks */
    assert(_msg != NULL); // command control hci_status indication message not null

    /* handle */
    uint8_t space[PROTOCOL_MESSAGE_IND_SIZE + PROTOCOL_MESSAGE_IND_BUFFER_SIZE] = {0};
    _msg->value.size = PROTOCOL_MESSAGE_IND_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_PROTOCOL_IND;
    *ptr++ = (uint8_t)_msg->result;
    for (int i = 0; i < _chunk->size && i < PROTOCOL_MESSAGE_IND_BUFFER_SIZE; ++i)
    {
        *ptr++ = _chunk->space[i];
        _msg->value.size++;
    }

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
