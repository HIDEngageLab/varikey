/**
 * \file cmd_param_firmware_msg.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Firmware message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_PARAM_FIRMWARE_MSG_H__
#define __CMD_PARAM_FIRMWARE_MSG_H__

#include "chunk.h"
#include "macros.h"

typedef struct chunk_struct chunk_t;

/** \brief Firmware request result */
typedef enum
{
    CMD_FIRMWARE_SUCCESS = SUCCESS,
    CMD_FIRMWARE_FAILURE = FAILURE,
    CMD_FIRMWARE_UNKNOWN = 0x02,
    CMD_FIRMWARE_UNSUPPORTED = 0x03,
} cmd_firmware_result_t;

/** \brief Firmware parameter */
typedef struct cmd_firmware_msg_struct
{
    cmd_firmware_result_t result;
    chunk_t value;
} cmd_firmware_msg_t;

extern void cmd_param_firmware_msg_req(chunk_t const *const _chunk, cmd_firmware_msg_t *const _msg);
extern void cmd_param_firmware_msg_cfm(cmd_firmware_msg_t *const _msg);

#endif /* __CMD_PARAM_FIRMWARE_MSG_H__ */
