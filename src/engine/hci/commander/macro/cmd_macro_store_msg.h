/**
 * \file cmd_macro_store_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Store message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_MACRO_STORE_MSG_H__
#define __CMD_MACRO_STORE_MSG_H__

#include "cmd_macro_msg.h"
#include "types.h"

typedef struct chunk_struct chunk_t;

extern void cmd_macro_store_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg);
extern void cmd_macro_store_msg_cfm(cmd_macro_ctrl_msg_t *const _msg);

extern void cmd_macro_store_msg_ind(cmd_macro_transport_msg_t *const _msg);
extern void cmd_macro_store_msg_res(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg);

#endif /* __CMD_MACRO_STORE_MSG_H__ */
