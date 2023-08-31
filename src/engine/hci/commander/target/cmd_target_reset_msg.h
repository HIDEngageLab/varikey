/**
 * \file cmd_target_reset_msg.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief target reset message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_TARGET_RESET_MSG_H__
#define __CMD_TARGET_RESET_MSG_H__

#include "chunk.h"
#include "cmd_target.h"
#include "macros.h"

typedef struct chunk_struct chunk_t;

/** \brief Target reset message result code */
typedef enum
{
    CMD_TARGET_RESET_RESULT_SUCCESS = SUCCESS,
    CMD_TARGET_RESET_RESULT_FAILURE = FAILURE,
    CMD_TARGET_RESET_RESULT_UNKNOWN_FUNCTION = 0x02,
} cmd_target_reset_result_t;

/** \brief target reset message function code */
typedef enum
{
    CMD_TARGET_RESET_FUNCTION_START = 0x00,
    CMD_TARGET_RESET_FUNCTION_STOP = 0x01,
    CMD_TARGET_RESET_FUNCTION_RESTART = 0x02,
} cmd_target_reset_function_t;

/** \brief target reset message */
typedef struct cmd_target_reset_msg_struct
{
    cmd_target_reset_result_t result;
    cmd_target_reset_function_t function;
    chunk_t value;
} cmd_target_reset_msg_t;

extern void cmd_target_reset_msg_req(chunk_t const *const _chunk, cmd_target_reset_msg_t *const _msg);
extern void cmd_target_reset_msg_cfm(cmd_target_reset_msg_t *const _msg);

#endif /* __CMD_TARGET_RESET_MSG_H__ */
