/**
 * \file cmd_macro_store_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Store message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_macro_store_msg.h"
#include "commander.h"
#include "macros.h"
#include "revision.h"
#include "serial_frame.h"
#include "storage_queue.h"

#define STORE_CFM_LENGTH 6
#define STORE_IND_LENGTH 10

/**
    \brief Store request message

    Deserialize only
*/
extern void cmd_macro_store_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* store macro request chunk null */

    /* deserialize */
    _msg->result = CMD_MACRO_SUCCESS;

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Store confirmation message
*/
extern void cmd_macro_store_msg_cfm(cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* store macro confirmation message null */

    /* handle */
    uint8_t space[STORE_CFM_LENGTH] = {0};
    _msg->value.size = STORE_CFM_LENGTH;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_MACRO_STORE_CFM;
    *ptr++ = (uint8_t)_msg->result;
    serialize_float(storage_get_free_memory_progress(), &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Store indication message
*/
extern void cmd_macro_store_msg_ind(cmd_macro_transport_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* store macro request chunk null */

    /* handle */
    uint8_t space[STORE_IND_LENGTH] = {0};
    _msg->value.size = STORE_IND_LENGTH;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_MACRO_STORE_IND;
    *ptr++ = (uint8_t)HIBYTE(_msg->index);
    *ptr++ = (uint8_t)LOBYTE(_msg->index);
    *ptr++ = (uint8_t)HIBYTE(_msg->max);
    *ptr++ = (uint8_t)LOBYTE(_msg->max);
    *ptr++ = (uint8_t)_msg->event.typed.type;
    if (_msg->event.typed.type == HIL_EVENT_KEY)
    {
        *ptr++ = (uint8_t)_msg->event.typed.common.key.id;
        *ptr++ = (uint8_t)_msg->event.typed.common.key.level;
        *ptr++ = 0;
        *ptr++ = 0;
    }
    else if (_msg->event.typed.type == HIL_EVENT_WHEEL)
    {
        serialize_float(_msg->event.typed.common.wheel.value, &ptr);
    }
    else if (_msg->event.typed.type == HIL_EVENT_DELAY)
    {
        serialize_float(_msg->event.typed.common.delay.value, &ptr);
    }

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Store response message
*/
extern void cmd_macro_store_msg_res(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* store macro request chunk null */
    /* deserialize */
    _msg->index = SETWORD(_chunk->space[0], _chunk->space[1]);
    _msg->max = SETWORD(_chunk->space[2], _chunk->space[3]);

    _msg->value.size = 0;
    _msg->value.space = 0;
}
