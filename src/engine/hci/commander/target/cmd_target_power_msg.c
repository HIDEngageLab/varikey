/**
 * \file cmd_target_power_msg.c
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief power message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdint.h>

#include <pico/stdlib.h>

#include "chunk.h"
#include "cmd_target_power_msg.h"
#include "commander.h"
#include "macros.h"
#include "serial_frame.h"

#define POWER_MESSAGE_CFM_SIZE 3
#define POWER_MESSAGE_IND_SIZE 6

static cmd_power_voltage_t get_voltage(uint8_t const _value);
static cmd_power_function_t get_fuction(uint8_t const _value);

/**
    \brief Status request message

    Deserialize only.
*/
extern void cmd_target_power_msg_req(chunk_t const *const _chunk, cmd_power_msg_t *const _msg)
{
    /* checks */
    assert(_chunk != NULL && _msg != NULL); // chunk is not null

    /* handle */
    _msg->function = get_fuction(_chunk->space[0]);

    if (_msg->function != CMD_TARGET_POWER_FUNCTION_UNDEFINED)
    {
        switch (_msg->function)
        {
        case CMD_TARGET_POWER_FUNCTION_GET:
            /* no payload */
            break;
        case CMD_TARGET_POWER_FUNCTION_OBSERVER_SET:
            _msg->voltage = get_voltage(_chunk->space[1]);
            if (_msg->voltage != CMD_TARGET_POWER_VOLTAGE_UNDEFINED)
            {
                uint8_t const *ptr = &_chunk->space[2];
                _msg->payload.trigger.limit_low = deserialize_float(&ptr);
                _msg->payload.trigger.limit_high = deserialize_float(&ptr);
            }
            break;
        case CMD_TARGET_POWER_FUNCTION_OBSERVER_RESET:
            _msg->voltage = get_voltage(_chunk->space[1]);
            break;
        case CMD_TARGET_POWER_FUNCTION_OBSERVER_INTERVAL:
        {
            uint8_t const *ptr = &_chunk->space[1];
            _msg->payload.interval.value = deserialize_long(&ptr);
            break;
        }
        default:
            break;
        }
    }

    _msg->value.size = 0;
    _msg->value.space = 0;
}

/**
    \brief Send power confirmation
*/
extern void cmd_target_power_msg_cfm(cmd_power_cfm_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command target power confirmation message not null

    /* handle */
    uint8_t space[POWER_MESSAGE_CFM_SIZE] = {0};
    _msg->value.size = POWER_MESSAGE_CFM_SIZE;
    _msg->value.space = space;
    uint8_t *ptr = space;

    *ptr++ = (uint8_t)HC_TARGET_POWER_CFM;
    *ptr++ = (uint8_t)_msg->result;
    *ptr++ = (uint8_t)_msg->function;

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

/**
    \brief Send power indication
*/
extern void cmd_target_power_msg_ind(cmd_power_ind_msg_t *const _msg)
{
    /* checks */
    assert(_msg != NULL); // command target power indication message not null

    /* handle */
    uint8_t ind_space[POWER_MESSAGE_IND_SIZE] = {0};
    _msg->value.size = POWER_MESSAGE_IND_SIZE;
    _msg->value.space = ind_space;
    uint8_t *ptr = ind_space;

    *ptr++ = (uint8_t)HC_TARGET_POWER_IND;
    *ptr++ = (uint8_t)_msg->voltage;
    serialize_float(_msg->power, &ptr);

    serial_frame_send(SERIAL_COMMANDER_INTERPRETER_ADDRESS, &_msg->value);
}

static cmd_power_voltage_t get_voltage(uint8_t const _value)
{
    if (_value == CMD_TARGET_POWER_VOLTAGE_1V8 ||
        _value == CMD_TARGET_POWER_VOLTAGE_3V2 ||
        _value == CMD_TARGET_POWER_VOLTAGE_5V0 ||
        _value == CMD_TARGET_POWER_VOLTAGE_SER_VBUS)
    {
        return _value;
    }

    return CMD_TARGET_POWER_VOLTAGE_UNDEFINED;
}

static cmd_power_function_t get_fuction(uint8_t const _value)
{
    if (_value == CMD_TARGET_POWER_FUNCTION_GET ||
        _value == CMD_TARGET_POWER_FUNCTION_OBSERVER_SET ||
        _value == CMD_TARGET_POWER_FUNCTION_OBSERVER_RESET ||
        _value == CMD_TARGET_POWER_FUNCTION_OBSERVER_INTERVAL)
    {
        return _value;
    }

    return CMD_TARGET_POWER_FUNCTION_UNDEFINED;
}
