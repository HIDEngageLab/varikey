/**
 * \file cmd_event_trigger.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Macro handling

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include "cmd_event_trigger.h"
#include "checksum.h"
#include "cmd_event_msg.h"
#include "cmd_macro_clean_msg.h"
#include "cmd_macro_key_msg.h"
#include "cmd_macro_load_msg.h"
#include "cmd_macro_msg.h"
#include "cmd_macro_session.h"
#include "composed_hid.h"
#include "engine.h"
#include "param_key.h"
#include "storage_interface.h"
#include "storage_queue.h"

#define MAX_NUMBER_OF_RETRY 3

static void send_confirmation(storage_result_t _result);

/**
    \brief Macro store request

    Sends a confirmation message and initialize macro download
*/
extern void cmd_event_trigger_request(chunk_t const *_chunk)
{
    cmd_event_msg_t msg;
    cmd_event_msg_req(_chunk, &msg);
    /*
        if (msg.result == CMD_EVENT_SUCCESS)
        {
            if (msg.event.type == HIL_EVENT_KEY)
            {
                if (msg.event.common.key.level == HIL_KEY_LEVEL_CLICK)
                {
                    msg.event.common.key.level = HIL_KEY_LEVEL_PRESS;
                    if (engine_event(&msg.event, 0) == FAILURE)
                    {
                        msg.result = CMD_EVENT_FAILURE;
                    }
                    msg.event.common.key.level = HIL_KEY_LEVEL_RELEASE;

                    const uint64_t click_us = g_key.button.click_ms * 1000;
                    engine_event(&msg.event, click_us);
                }
                else if (msg.event.common.key.level == HIL_KEY_LEVEL_PUSH)
                {
                    msg.event.common.key.level = HIL_KEY_LEVEL_PRESS;
                    if (engine_event(&msg.event, 0) == FAILURE)
                    {
                        msg.result = CMD_EVENT_FAILURE;
                    }
                    msg.event.common.key.level = HIL_KEY_LEVEL_RELEASE;

                    const uint64_t push_us = g_key.button.push_ms * 1000;
                    engine_event(&msg.event, push_us);
                }
                else
                {
                    if (engine_event(&msg.event, 0) == FAILURE)
                    {
                        msg.result = CMD_EVENT_FAILURE;
                    }
                }
            }
            else
            {
                if (engine_event(&msg.event, 0) == FAILURE)
                {
                    msg.result = CMD_EVENT_FAILURE;
                }
            }
        }
    */

    cmd_event_msg_cfm(&msg);
}

/**
    \brief Send a event trigger confirmation

    \param _result operation result
 */
static void send_confirmation(storage_result_t _result)
{
    cmd_event_msg_t msg;
    msg.result = _result;

    cmd_event_msg_cfm(&msg);
}

/**
    \brief Send hil power event

    \param _event power event
 */
/*
extern void hil_event_power_trigger(hil_event_power_t *const _event)
{
    cmd_event_msg_t msg;
    msg.event.type = HIL_EVENT_POWER;
    msg.event.common.power.voltage = _event->voltage;
    msg.event.common.power.level = _event->level;
    msg.event.common.power.value = _event->value;
    msg.event.common.power.limit_low = _event->limit_low;
    msg.event.common.power.limit_high = _event->limit_high;

    cmd_event_msg_ind(&msg);
}
*/