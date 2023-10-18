/**
 * \file cmd_param_identity_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Identifier message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>

#include "chunk.h"
#include "cmd_param_identity_msg.h"
#include "commander.h"
#include "macros.h"
#include "param_maintainer.h"
#include "param_serial_number.h"
#include "revision.h"
#include "serial_frame.h"

#define IDENTITY_CFM_PAYLOAD_LENGTH 15

/**
    \brief Identity request

    Deserialize only.
*/
extern void cmd_param_identity_req(chunk_t const *const _chunk, cmd_identity_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* identity param request chunk null */
    /* handle */
    _msg->part = _chunk->space[0];

    if (_msg->part == CMD_IDENTITY_SERIAL || _msg->part == CMD_IDENTITY_PLATFORM)
    {
        _msg->result = CMD_IDENTITY_SUCCESS;
    }
    else
    {
        _msg->result = CMD_IDENTITY_UNSUPPORTED;
    }

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Send Identity confirmation

    Identities:
    - Serial number
    - Platform identifier (maintainer and hw revision)
*/
extern void cmd_param_identity_cfm(cmd_identity_msg_t *const _msg)
{
    assert(_msg != NULL); // identity confirmation message null

    /*  space for message chunk */
    uint8_t cfm_space[IDENTITY_CFM_PAYLOAD_LENGTH] = {0};
    _msg->value.space = cfm_space;
    uint8_t *ptr = cfm_space;

    *ptr++ = (uint8_t)HC_IDENTITY_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->part;
    _msg->value.size = 3;

    if (_msg->part == CMD_IDENTITY_SERIAL)
    {
        param_serial_number_serialize(ptr);
        _msg->value.size += PARAMETER_SERIAL_NUMBER_SIZE;
    }
    else if (_msg->part == CMD_IDENTITY_PLATFORM)
    {
        *ptr++ = (uint8_t)g_maintainer.byte;
        *ptr++ = (uint8_t)HIBYTE(HARDWARE_IDENTIFIER);
        *ptr++ = (uint8_t)LOBYTE(HARDWARE_IDENTIFIER);
        *ptr++ = (uint8_t)HARDWARE_NUMBER;
        _msg->value.size += 4;
    }

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
