/**
 * \file cmd_param_param_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "cmd_param_param_msg.h"
#include "commander.h"
#include "serial_frame.h"

#define PARAMETER_MSG_CFM_SIZE 4

/**
    \brief De-serialize parameter request
*/
extern void cmd_param_param_msg_req(chunk_t const *const _chunk, cmd_param_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* param message chunk null */

    /* deserialize */
    _msg->identifier = _chunk->space[0];
    _msg->function = _chunk->space[1];

    /* attention: parameter get requests coming in without value payload */
    if (_msg->function == CMD_PARAM_FUNCTION_GET)
    {
        _msg->value.size = 0;
        _msg->value.space = NULL;
    }
    else
    {
        _msg->value.size = _chunk->size - 2;
        _msg->value.space = &_chunk->space[2];
    }
}

/**
    \brief Serialize and send parameter confirmation
*/
extern void cmd_param_param_msg_cfm(cmd_param_msg_t const *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* param message null */

    /* serialize */
    const uint8_t len = PARAMETER_MSG_CFM_SIZE + _msg->value.size;
    uint8_t space[len];
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_PARAM_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->identifier;
    *ptr++ = (uint8_t)_msg->function;

    uint8_t *value_ptr = _msg->value.space;
    for (uint8_t i = 0; i < _msg->value.size; ++i)
    {
        *ptr++ = *value_ptr++;
    }

    /* send */
    chunk_t cfm_sdu = {space, len};
    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &cfm_sdu);
}
