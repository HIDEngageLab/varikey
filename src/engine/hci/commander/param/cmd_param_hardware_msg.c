/**
 * \file cmd_param_hardware_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Hardware number message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "cmd_param_hardware_msg.h"
#include "commander.h"
#include "revision.h"
#include "serial_frame.h"

#define PARAM_HARDWARE_MSG_CFM_SIZE 5

/**
    \brief Hardware request message
*/
extern void cmd_param_hardware_msg_req(chunk_t const *const _chunk, cmd_hardware_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* hardware param request chunk null */

    /* deserialize */
    _msg->result = CMD_HARDWARE_SUCCESS;
    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Send confirmation
*/
extern void cmd_param_hardware_msg_cfm(cmd_hardware_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* hardware param confirmation chunk null */

    /* handle */
    uint8_t cfm_space[PARAM_HARDWARE_MSG_CFM_SIZE] = {0};
    _msg->value.size = PARAM_HARDWARE_MSG_CFM_SIZE;
    _msg->value.space = cfm_space;
    uint8_t *ptr = cfm_space;

    *ptr++ = (uint8_t)HC_HARDWARE_CFM;
    *ptr++ = (uint8_t)_msg->result;
    serialize_word(HARDWARE_IDENTIFIER, &ptr);
    *ptr++ = (uint8_t)HARDWARE_REVISION;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
