/**
 * \file cmd_control_status_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief status message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <pico/stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "chunk.h"
#include "cmd_control_status_msg.hpp"
#include "commander.hpp"
#include "component_state.hpp"
#include "engine.hpp"
#include "macros.hpp"
#include "param_serial_number.hpp"
#include "serial_frame.hpp"
#include "storage_queue.hpp"

#define CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE 13
#define CMD_CONTROL_STATUS_MESSAGE_IND_SIZE 7

/**
    \brief Status request message

    Deserialize only.
*/
extern void cmd_control_status_msg_req(chunk_t const *const _chunk, cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); // chunk is not null

    /* deserialize */
    _msg->result = CMD_STATUS_RESULT_FAILURE;
    _msg->function = static_cast<cmd_status_function_t>(_chunk->space[0]);

    const pulp::COMPONENT_STATE mode = engine_mode_get();
    switch (mode)
    {
    case pulp::COMPONENT_STATE::IDLE:
        _msg->mode = CMD_MODE_IDLE;
        break;

    case pulp::COMPONENT_STATE::ACTIVE:
        _msg->mode = CMD_MODE_ACTIVE;
        break;

    case pulp::COMPONENT_STATE::PENDING:
        _msg->mode = CMD_MODE_PENDING;
        break;

    default:
        _msg->mode = CMD_MODE_UNDEFINED;
        break;
    }

    /*
    const engine_operation_t operation = engine_operation_get();
    switch (operation)
    {
    case ENGINE_OPERATION_PLAY:
        _msg->operation = CMD_OPERATION_PLAY;
        break;

    case ENGINE_OPERATION_RECORD:
        _msg->operation = CMD_OPERATION_RECORD;
        break;

    default:
        _msg->operation = CMD_OPERATION_UNDEFINED;
        break;
    }
    */

    _msg->value.size = _chunk->size - 1;
    _msg->value.space = &_chunk->space[1];

    /* trigger status/operation event */
    if (_msg->function == CMD_STATUS_FUNCTION_GET)
    {
        _msg->result = CMD_STATUS_RESULT_SUCCESS;
    }
    else
    {
        if (_msg->function == CMD_STATUS_FUNCTION_START)
        {
            if (_msg->operation != CMD_OPERATION_UNDEFINED)
            {
                if (mode == pulp::COMPONENT_STATE::IDLE)
                {
                    _msg->result = CMD_STATUS_RESULT_SUCCESS;
                }
                else
                {
                    _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
                }
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_OPERATION;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_STOP)
        {
            if (mode == pulp::COMPONENT_STATE::ACTIVE ||
                mode == pulp::COMPONENT_STATE::PENDING)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_PLAY)
        {
            if (mode == pulp::COMPONENT_STATE::IDLE)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else if (_msg->function == CMD_STATUS_FUNCTION_RECORD)
        {
            if (mode == pulp::COMPONENT_STATE::IDLE)
            {
                _msg->result = CMD_STATUS_RESULT_SUCCESS;
            }
            else
            {
                _msg->result = CMD_STATUS_RESULT_WRONG_MODE;
            }
        }
        else
        {
            _msg->result = CMD_STATUS_RESULT_UNKNOWN_FUNCTION;
        }
    }
}

/**
    \brief Send status confirmation
*/
extern void cmd_control_status_msg_cfm(cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control status confirmation message not null

    /* space */
    uint8_t space[CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_STATUS_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_STATUS_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->function;
    *ptr++ = (uint8_t)_msg->operation;
    *ptr++ = (uint8_t)_msg->mode;
    serialize_float(storage_get_free_memory_progress(), &ptr);
    serialize_long(g_unique_key, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Send status indication
*/
extern void cmd_control_status_msg_ind(cmd_status_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command control status indication message not null

    /* handle */
    uint8_t space[CMD_CONTROL_STATUS_MESSAGE_IND_SIZE] = {0};
    _msg->value.size = CMD_CONTROL_STATUS_MESSAGE_IND_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_STATUS_IND;
    *ptr++ = (uint8_t)_msg->operation;
    *ptr++ = (uint8_t)_msg->mode;
    serialize_float(storage_get_free_memory_progress(), &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}
