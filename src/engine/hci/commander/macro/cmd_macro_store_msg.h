/**
 * \file cmd_macro_store_msg.h
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Store message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_STORE_MSG_H__
#define __CMD_MACRO_STORE_MSG_H__

#include "cmd_macro_msg.h"
#include "macros.h"

typedef struct chunk_struct chunk_t;

extern void cmd_macro_store_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg);
extern void cmd_macro_store_msg_cfm(cmd_macro_ctrl_msg_t *const _msg);

extern void cmd_macro_store_msg_ind(cmd_macro_transport_msg_t *const _msg);
extern void cmd_macro_store_msg_res(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg);

#endif /* __CMD_MACRO_STORE_MSG_H__ */
