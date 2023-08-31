/**
 * \file cmd_control_temperature_msg.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Temperature message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <stddef.h>
#include <stdint.h>

#include <pico/stdlib.h>

#include "chunk.h"
#include "cmd_control_temperature_msg.h"
#include "commander.h"
#include "macros.h"
#include "serial_frame.h"
#include "temperature.h"

#define CMD_CONTROL_TEMPERATURE_MESSAGE_CFM_SIZE 6
#define CMD_CONTROL_TEMPERATURE_MESSAGE_IND_SIZE 5

/**
    \brief Temperature request message

    Deserialize only.
*/
extern void cmd_control_temperature_msg_req(chunk_t const *const _chunk, cmd_temperature_msg_t *const _msg)
{
    (void)_chunk;
    /* checks */
    assert(_msg != NULL); // message is not null

    _msg->result = CMD_TEMPERATURE_RESULT_SUCCESS;
    _msg->temperature = temperature_get();
}

/**
    \brief Send temperature confirmation
*/
extern void cmd_control_temperature_msg_cfm(cmd_temperature_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control temperature confirmation message not null

    /* handle */
    uint8_t space[CMD_CONTROL_TEMPERATURE_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_TEMPERATURE_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_TEMPERATURE_CFM;
    *ptr++ = (uint8_t)_msg->result;
    serialize_float(_msg->temperature, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Send temperature indication
*/
extern void cmd_control_temperature_msg_ind(cmd_temperature_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control temperature indication message NULL

    /* handle */
    uint8_t space[CMD_CONTROL_TEMPERATURE_MESSAGE_IND_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_TEMPERATURE_MESSAGE_IND_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_TEMPERATURE_IND;
    serialize_float(_msg->temperature, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
