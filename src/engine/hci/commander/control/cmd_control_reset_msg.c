/**
 * \file cmd_control_reset_msg.c
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

#include <pico/stdlib.h>
#include <stddef.h>

#include "chunk.h"
#include "cmd_control_reset_msg.h"
#include "commander.h"
#include "serial_frame.h"

#define RESET_MESSAGE_IND_SIZE 2

/**
    \brief Reset request message

    (Message handling isn't required here)
*/
extern void cmd_control_reset_msg_req(chunk_t const *const _chunk, cmd_reset_msg_t *const _msg)
{
    /* checks */
    (void)_chunk;
    assert(_msg != NULL); // reset request message null

    /* handle */
    _msg->result = CMD_RESET_RESULT_SUCCESS;
    _msg->function = _chunk->space[0];

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Reset indication message
*/
extern void cmd_control_reset_msg_ind(cmd_reset_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* command control reset message null */

    /* handle */
    uint8_t space[RESET_MESSAGE_IND_SIZE] = {0};
    _msg->value.size = RESET_MESSAGE_IND_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_RESET_IND;
    *ptr++ = (uint8_t)_msg->result;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
