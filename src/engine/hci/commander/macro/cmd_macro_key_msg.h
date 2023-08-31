/**
 * \file cmd_macro_key_msg.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Key message

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __CMD_MACRO_KEY_MSG_H__
#define __CMD_MACRO_KEY_MSG_H__

#include "cmd_macro_msg.h"

typedef struct chunk_struct chunk_t;

extern void cmd_macro_key_msg_req(chunk_t const *const _chunk, cmd_macro_key_msg_t *const _msg);
extern void cmd_macro_key_msg_cfm(cmd_macro_key_msg_t *const _msg);

#endif /* __CMD_MACRO_KEY_MSG_H__ */
