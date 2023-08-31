/**
 * \file cmd_control_temperature_msg.h
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

#ifndef __CMD_CONTROL_TEMPERATURE_MSG_H__
#define __CMD_CONTROL_TEMPERATURE_MSG_H__

#include "macros.h"

typedef struct chunk_struct chunk_t;

/** \brief Temperature message result code */
typedef enum
{
    CMD_TEMPERATURE_RESULT_SUCCESS = SUCCESS,
    CMD_TEMPERATURE_RESULT_FAILURE = FAILURE,
} cmd_temperature_result_t;

/** \brief Temperature message */
typedef struct cmd_temperature_msg_struct
{
    cmd_temperature_result_t result;
    float temperature;
    chunk_t value;
} cmd_temperature_msg_t;

extern void cmd_control_temperature_msg_req(chunk_t const *const _chunk, cmd_temperature_msg_t *const _msg);
extern void cmd_control_temperature_msg_cfm(cmd_temperature_msg_t *const _msg);
extern void cmd_control_temperature_msg_ind(cmd_temperature_msg_t *const _msg);

#endif /*  __CMD_CONTROL_TEMPERATURE_MSG_H__ */
