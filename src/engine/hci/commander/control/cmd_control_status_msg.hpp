/**
 * \file cmd_control_status_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief status message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_CONTROL_STATUS_MSG_HPP__
#define __CMD_CONTROL_STATUS_MSG_HPP__

#include "chunk.h"
#include "macros.hpp"

/** \brief Status message mode type */
typedef enum
{
    CMD_MODE_IDLE = 0x00,
    CMD_MODE_ACTIVE = 0x01,
    CMD_MODE_PENDING = 0x02,
    CMD_MODE_UNDEFINED = 0xff,
} cmd_mode_t;

typedef enum
{
    CMD_OPERATION_RECORD = 0x00,    // node (no host controller, infrastructure, no HCI)
    CMD_OPERATION_PLAY = 0x01,      // tag (host controller, HCI enabled)
    CMD_OPERATION_UNDEFINED = 0xff, // not prepared
} cmd_operation_t;

/** \brief Status request/confirmation function value */
typedef enum
{
    CMD_STATUS_FUNCTION_GET = 0x00,
    CMD_STATUS_FUNCTION_START = 0x05,
    CMD_STATUS_FUNCTION_STOP = 0x06,
    CMD_STATUS_FUNCTION_RECORD = 0x07,
    CMD_STATUS_FUNCTION_PLAY = 0x08,
} cmd_status_function_t;

/** \brief Status message result code */
typedef enum
{
    CMD_STATUS_RESULT_SUCCESS = SUCCESS,
    CMD_STATUS_RESULT_FAILURE = FAILURE,
    CMD_STATUS_RESULT_UNKNOWN_FUNCTION = 0x02,
    CMD_STATUS_RESULT_WRONG_OPERATION = 0x03,
    CMD_STATUS_RESULT_WRONG_MODE = 0x04,
    CMD_STATUS_RESULT_IDENTIFIER_EXISTS = 0x05,
} cmd_status_result_t;

/** \brief Status message */
typedef struct cmd_status_msg_struct
{
    cmd_status_result_t result;
    cmd_status_function_t function;
    cmd_mode_t mode;
    cmd_operation_t operation;
    chunk_t value;
} cmd_status_msg_t;

extern void cmd_control_status_msg_req(chunk_t const *const _chunk, cmd_status_msg_t *const _msg);
extern void cmd_control_status_msg_cfm(cmd_status_msg_t *const _msg);
extern void cmd_control_status_msg_ind(cmd_status_msg_t *const _msg);

#endif /*  __CMD_CONTROL_STATUS_MSG_HPP__ */
