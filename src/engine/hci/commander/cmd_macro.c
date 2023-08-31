/**
 * \file cmd_macro.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Macro handling

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "cmd_macro.h"
#include "checksum.h"
#include "cmd_event_msg.h"
#include "cmd_macro_clean_msg.h"
#include "cmd_macro_key_msg.h"
#include "cmd_macro_load_msg.h"
#include "cmd_macro_msg.h"
#include "cmd_macro_session.h"
#include "cmd_macro_store_msg.h"
#include "composed_hid.h"
#include "storage_interface.h"
#include "storage_queue.h"

/**
    \brief Macro key request

    Sends a confirmation message with a hash value
*/
extern void cmd_macro_key_request(chunk_t const *_chunk)
{
    cmd_macro_key_msg_t msg;
    cmd_macro_key_msg_req(_chunk, &msg);

    msg.hash = checksum_hash(_chunk);

    cmd_macro_key_msg_cfm(&msg);
}

/**
    \brief Macro storage clean

    Sends a confirmation and clean the macro storage
*/
extern void cmd_macro_clean_request(chunk_t const *_chunk)
{
    cmd_macro_ctrl_msg_t msg;
    cmd_macro_clean_msg_req(_chunk, &msg);

    storage_result_t result = storage_erase();
    if (result == STORAGE_SUCCESS)
    {
        msg.result = CMD_MACRO_SUCCESS;
    }
    else if (result == STORAGE_BUSY)
    {
        msg.result = CMD_MACRO_BUSY;
    }
    else
    {
        msg.result = CMD_MACRO_FAILURE;
    }

    cmd_macro_clean_msg_cfm(&msg);
}
