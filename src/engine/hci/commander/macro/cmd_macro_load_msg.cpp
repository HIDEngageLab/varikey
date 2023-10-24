/**
 * \file cmd_macro_load_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Load message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_macro_load_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "revision.h"
#include "serial_frame.hpp"
#include "storage_queue.hpp"

#define LOAD_CFM_LENGTH 6
#define LOAD_IND_LENGTH 5

/**
    \brief Load request message

    Deserialize only
*/
extern void cmd_macro_load_msg_req(chunk_t const *const _chunk, cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* load macro request chunk null */

    /* deserialize */
    _msg->result = CMD_MACRO_SUCCESS;
    _msg->max = SETWORD(_chunk->space[0], _chunk->space[1]);

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Load confirmation message
*/
extern void cmd_macro_load_msg_cfm(cmd_macro_ctrl_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* load macro confirmation message null */

    /* handle */
    uint8_t space[LOAD_CFM_LENGTH] = {0};
    _msg->value.size = LOAD_CFM_LENGTH;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_MACRO_LOAD_CFM;
    *ptr++ = (uint8_t)_msg->result;
    serialize_float(storage_get_free_memory_progress(), &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Load indication message
*/
extern void cmd_macro_load_msg_ind(cmd_macro_transport_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); /* load macro request chunk null */

    /* handle */
    uint8_t space[LOAD_IND_LENGTH] = {0};
    _msg->value.size = LOAD_IND_LENGTH;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_MACRO_LOAD_IND;
    *ptr++ = (uint8_t)HIBYTE(_msg->index);
    *ptr++ = (uint8_t)LOBYTE(_msg->index);
    *ptr++ = (uint8_t)HIBYTE(_msg->max);
    *ptr++ = (uint8_t)LOBYTE(_msg->max);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Load response message
*/
extern void cmd_macro_load_msg_res(chunk_t const *const _chunk, cmd_macro_transport_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); /* load macro request chunk null */

    _msg->index = SETWORD(_chunk->space[0], _chunk->space[1]);
    _msg->max = SETWORD(_chunk->space[2], _chunk->space[3]);
    _msg->event.typed.type = static_cast<hci_event_type_t>(_chunk->space[4]);
    if (_msg->event.typed.type == HIL_EVENT_KEY)
    {
        _msg->event.typed.common.key.id = static_cast<hci_key_identifier_t>(_chunk->space[5]);
        _msg->event.typed.common.key.level = static_cast<hci_key_level_t>(_chunk->space[6]);
    }
    else if (_msg->event.typed.type == HIL_EVENT_WHEEL)
    {
        uint8_t const *ptr = &_chunk->space[5];
        _msg->event.typed.common.wheel.value = deserialize_float(&ptr);
    }
    else if (_msg->event.typed.type == HIL_EVENT_DELAY)
    {
        uint8_t const *ptr = &_chunk->space[5];
        _msg->event.typed.common.delay.value = deserialize_float(&ptr);
    }
    else
    {
        for (int i = 0; i < HIL_EVENT_VALUE_SIZE; ++i)
        {
            _msg->event.value[i] = 0;
        }
    }

    _msg->value.size = 0;
    _msg->value.space = 0;
}
