/**
 * \file cmd_target_reset_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief reset message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdint.h>

#include <pico/stdlib.h>

#include "chunk.h"
#include "cmd_target_reset_msg.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"

#define RESET_MESSAGE_CFM_SIZE 3

/**
    \brief Status request message

    Deserialize only.
*/
extern void cmd_target_reset_msg_req(chunk_t const *const _chunk, cmd_target_reset_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); // chunk is not null

    /* handle */
    _msg->function = static_cast<cmd_target_reset_function_t>(_chunk->space[0]);

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Send reset confirmation
*/
extern void cmd_target_reset_msg_cfm(cmd_target_reset_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command target reset confirmation message not null

    /* handle */
    uint8_t space[RESET_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = RESET_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_TARGET_RESET_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->function;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
