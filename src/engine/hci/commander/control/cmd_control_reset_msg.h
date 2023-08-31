/**
 * \file cmd_control_reset_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Reset message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_CONTROL_RESET_MSG_H__
#define __CMD_CONTROL_RESET_MSG_H__

#include "types.h"

typedef struct chunk_struct chunk_t;

/** \brief Status request/confirmation function value */
typedef enum
{
    CMD_RESET_FUNCTION_SHUTDOWN = 0x00,
    CMD_RESET_FUNCTION_FORMAT = 0x01,
} cmd_reset_function_t;

/** \brief Reset message result type */
typedef enum cmd_reset_result_enum
{
    CMD_RESET_RESULT_SUCCESS = SUCCESS,               //< initialization done
    CMD_RESET_RESULT_ERROR = FAILURE,                 //< initialization failed
    CMD_RESET_RESULT_CRITICAL_ERROR = 0x02,           //< initialization failed (hw disabled, safe state)
    CMD_RESET_RESULT_WATCHDOG = 0x03,                 //< reboot after watchdog
    CMD_RESET_RESULT_PARAMETER_MISSED = 0x04,         //< parameter storage dropped
    CMD_RESET_RESULT_PARAMETER_RESTORED = 0x05,       //< parameter storage (re)created, maintainer parameters restored from backup
    CMD_RESET_RESULT_PARAMETER_RECREATED = 0x06,      //< parameter storage (re)created, no maintainer parameter backup available (radio disabled)
    CMD_RESET_RESULT_PARAMETER_BACKUP_CREATED = 0x07, //< no valid maintainer parameter backup
} cmd_reset_result_t;

/** \brief Reset message */
typedef struct cmd_reset_msg_struct
{
    cmd_reset_result_t result;
    cmd_reset_function_t function;
    chunk_t value;
} cmd_reset_msg_t;

extern void cmd_control_reset_msg_req(chunk_t const *const _chunk, cmd_reset_msg_t *const _msg);
extern void cmd_control_reset_msg_ind(cmd_reset_msg_t *const _msg);

#endif /*  __CMD_CONTROL_RESET_MSG_H__ */
