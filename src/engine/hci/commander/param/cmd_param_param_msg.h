/**
 * \file cmd_param_param_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_PARAM_PARAMETER_MSG_H__
#define __CMD_PARAM_PARAMETER_MSG_H__

#include <stdint.h>

#include "chunk.h"
#include "macros.h"
#include "parameter.h"

/** \brief Parameter length type */
typedef enum
{
    CMD_PARAM_TYPELEN_BYTE = 0x01,
    CMD_PARAM_TYPELEN_WORD = 0x02,
    CMD_PARAM_TYPELEN_LONG = 0x04,
    CMD_PARAM_TYPELEN_BUFF = 0x80,
} cmd_param_typelen_t;

/** \brief parameter request function type */
typedef enum
{
    CMD_PARAM_FUNCTION_GET = 0x00,
    CMD_PARAM_FUNCTION_SET = 0x01,
} cmd_param_function_t;

/** \brief Parameter request result type */
typedef enum
{
    CMD_PARAM_SUCCESS = SUCCESS,
    CMD_PARAM_FAILURE = FAILURE,
    CMD_PARAM_UNKNOWN = 0x02,
    CMD_PARAM_UNSUPPORTED = 0x03,
    CMD_PARAM_STORAGE_ERROR = 0x04,
} cmd_param_result_t;

/** \brief Parameter message */
typedef struct cmd_param_msg_struct
{
    cmd_param_result_t result;
    param_identifier_t identifier;
    cmd_param_function_t function;
    chunk_t value;
} cmd_param_msg_t;

extern void cmd_param_param_msg_req(chunk_t const *const _chunk, cmd_param_msg_t *const _msg);
extern void cmd_param_param_msg_cfm(cmd_param_msg_t const *const _msg);

#endif /* __CMD_PARAM_PARAMETER_MSG_H__ */
