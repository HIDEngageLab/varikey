/**
 * \file cmd_event_msg.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Event message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_EVENT_MSG_H__
#define __CMD_EVENT_MSG_H__

#include "cmd_macro_msg.h"

typedef struct chunk_struct chunk_t;

/** \brief Macro result */
typedef enum
{
    CMD_EVENT_SUCCESS = SUCCESS,
    CMD_EVENT_FAILURE = FAILURE,
    CMD_EVENT_UNKNOWN_EVENT = 0x02,
    CMD_EVENT_WRONG_VALUE = 0x03,
    CMD_EVENT_WRONG_OPERATION = 0x04,
} cmd_event_result_t;

/**
    \brief Macro event message

    Event request und confirmation
    Trigger indication
*/
typedef struct cmd_macro_event_msg_struct
{
    cmd_event_result_t result;
    hil_event_typed_t event;
    chunk_t value;
} cmd_event_msg_t;

extern void cmd_event_msg_req(chunk_t const *const _chunk, cmd_event_msg_t *const _msg);
extern void cmd_event_msg_cfm(cmd_event_msg_t *const _msg);
extern void cmd_event_msg_ind(cmd_event_msg_t *const _msg);

#endif /* __CMD_EVENT_MSG_H__ */
