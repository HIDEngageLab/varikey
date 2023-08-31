/**
 * \file cmd_hci_status_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief HCI status message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_PROTOCOL_MSG_H__
#define __CMD_PROTOCOL_MSG_H__

#include "chunk.h"
#include "types.h"

typedef struct chunk_struct chunk_t;

/** \brief Status message result code */
typedef enum
{
    CMD_PROTOCOL_RESULT_SUCCESS = SUCCESS,
    CMD_PROTOCOL_RESULT_FAILURE = FAILURE,
    CMD_PROTOCOL_RESULT_INVALID_COMMAND = 0x02,
    CMD_PROTOCOL_RESULT_UNSUPPORTED = 0x03,
} cmd_hci_status_result_t;

/** \brief Status message */
typedef struct cmd_hci_status_msg_struct
{
    cmd_hci_status_result_t result;
    chunk_t value;
} cmd_hci_status_msg_t;

extern void cmd_hci_status_msg_ind(cmd_hci_status_msg_t *const _msg, chunk_t const *const _chunk);

#endif /* __CMD_PROTOCOL_MSG_H__ */
