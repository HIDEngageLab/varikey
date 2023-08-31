/**
 * \file cmd_param_hardware_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Hardware message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_PARAM_HARDWARE_MSG_H__
#define __CMD_PARAM_HARDWARE_MSG_H__

#include "types.h"

typedef struct chunk_struct chunk_t;

/** \brief Hardware request result */
typedef enum
{
    CMD_HARDWARE_SUCCESS = SUCCESS,
    CMD_HARDWARE_FAILURE = FAILURE,
    CMD_HARDWARE_UNKNOWN = 0x02,
    CMD_HARDWARE_UNSUPPORTED = 0x03,
} cmd_hardware_result_t;

/** \brief Hardware description parameter */
typedef struct cmd_hardware_msg_struct
{
    cmd_hardware_result_t result;
    chunk_t value;
} cmd_hardware_msg_t;

extern void cmd_param_hardware_msg_req(chunk_t const *const _chunk, cmd_hardware_msg_t *const _msg);
extern void cmd_param_hardware_msg_cfm(cmd_hardware_msg_t *const _msg);

#endif /* __CMD_PARAM_HARDWARE_MSG_H__ */
