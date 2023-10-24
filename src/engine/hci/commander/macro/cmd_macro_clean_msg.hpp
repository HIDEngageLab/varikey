/**
 * \file cmd_macro_clean_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Clean message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_CLEAN_MSG_HPP__
#define __CMD_MACRO_CLEAN_MSG_HPP__

#include "cmd_macro_msg.hpp"

typedef struct chunk_struct chunk_t;

extern void cmd_macro_clean_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg);
extern void cmd_macro_clean_msg_cfm(cmd_macro_ctrl_msg_t *const _msg);

#endif /* __CMD_MACRO_CLEAN_MSG_HPP__ */
