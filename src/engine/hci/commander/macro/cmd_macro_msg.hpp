/**
 * \file cmd_macro_msg.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Macro message common definitions

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __CMD_MACRO_MSG_HPP__
#define __CMD_MACRO_MSG_HPP__

#include "chunk.h"
#include "hci_event.hpp"
#include "macros.hpp"

/** \brief Macro result */
typedef enum
{
    CMD_MACRO_SUCCESS = SUCCESS,
    CMD_MACRO_FAILURE = FAILURE,
    CMD_MACRO_UNKNOWN_FUNCTION = 0x02,
    CMD_MACRO_WRONG_OPERATION = 0x03,
    CMD_MACRO_WRONG_MODE = 0x04,
    CMD_MACRO_OUT_OF_MEMORY = 0x05,
    CMD_MACRO_BUSY = 0x06,
    CMD_MACRO_EMPTY = 0x07,
} cmd_macro_result_t;

/**
    \brief Store macro control req/cfm message
*/
typedef struct cmd_macro_ctrl_msg_struct
{
    cmd_macro_result_t result;
    uint16_t index;
    uint16_t max;
    chunk_t value;
} cmd_macro_ctrl_msg_t;

/**
    \brief Store macro ind/res message

    Attention: used for load and store messages; contains unused fields.
*/
typedef struct cmd_macro_transport_msg_struct
{
    uint16_t index;
    uint16_t max;
    hci_event_t event;
    chunk_t value;
} cmd_macro_transport_msg_t;

/**
    \brief Store macro req/cfm message
*/
typedef struct cmd_macro_key_msg_struct
{
    cmd_macro_result_t result;
    uint32_t hash;
    chunk_t value;
} cmd_macro_key_msg_t;

#endif /* __CMD_MACRO_MSG_HPP__ */
