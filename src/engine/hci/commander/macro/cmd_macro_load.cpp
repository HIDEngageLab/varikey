/**
 * \file cmd_macro_load.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/*
    \brief Macro handling: upload

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "cmd_macro_load.hpp"
#include "checksum.hpp"
#include "cmd_macro_clean_msg.hpp"
#include "cmd_macro_key_msg.hpp"
#include "cmd_macro_load_msg.hpp"
#include "cmd_macro_msg.hpp"
#include "cmd_macro_session.hpp"
#include "cmd_macro_store_msg.hpp"
#include "composed_hid.hpp"
#include "storage_interface.hpp"
#include "storage_queue.hpp"

#define MAX_NUMBER_OF_RETRY 5
#define RETRY_TIMEOUT_MS 5000

static session_t session_record;

static int64_t retry_timer_callback(alarm_id_t id, void *user_data);

static void reset_session(void);
static void send_confirmation(storage_result_t _result, uint16_t _max);
static void send_indication(uint16_t _index, uint16_t _max);

/**
    \brief Macro load request

    Sends a confirmation message and initialize macro upload
*/
extern void cmd_macro_load_request(chunk_t const *_chunk)
{
    cmd_macro_ctrl_msg_t msg;
    cmd_macro_load_msg_req(_chunk, &msg);

    if (session_record.state == SESSION_IDLE)
    {
        session_record.state = SESSION_ACTIVE;

        session_record.data.index = 0;
        session_record.data.max = msg.max;

        storage_result_t result = storage_load_start(&session_record.data);
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
    }
    else
    {
        // SESSION_IDLE?
        msg.result = CMD_MACRO_WRONG_MODE;
    }

    cmd_macro_load_msg_cfm(&msg);

    if (msg.result == CMD_MACRO_SUCCESS)
    {
        if (session_record.data.index <= session_record.data.max)
        {
            send_indication(session_record.data.index, session_record.data.max);
            session_record.retry_counter = 0;
            session_record.timeout_id = add_alarm_in_ms(RETRY_TIMEOUT_MS, retry_timer_callback, NULL, true);
        }
    }
    else
    {
        session_record.state = SESSION_ACTIVE;
    }
}

/**
    \brief Macro load response

    Sends a confirmation message and initialize macro upload
*/
extern void cmd_macro_load_response(chunk_t const *_chunk)
{
    cmd_macro_transport_msg_t msg;
    cmd_macro_load_msg_res(_chunk, &msg);

    cancel_alarm(session_record.timeout_id);
    if (session_record.state == SESSION_ACTIVE)
    {
        if (msg.index == session_record.data.index && msg.max == session_record.data.max)
        {
            session_record.data.index = msg.index;
            session_record.data.max = msg.max;
            session_record.data.event = msg.event;

            storage_result_t result = storage_load_continue(&session_record.data);
            if (result == STORAGE_SUCCESS)
            {
                if (session_record.data.index == session_record.data.max)
                {
                    reset_session();
                }
                else
                {
                    if (session_record.data.index++ < session_record.data.max)
                    {
                        session_record.retry_counter = 0;
                        send_indication(session_record.data.index, session_record.data.max);
                        session_record.timeout_id = add_alarm_in_ms(RETRY_TIMEOUT_MS, retry_timer_callback, NULL, true);
                    }
                    else
                    {
                        reset_session();
                    }
                }
            }
            else if (result == STORAGE_BUSY)
            {
                send_confirmation(static_cast<storage_result_t>(CMD_MACRO_BUSY),
                                  session_record.data.max);
            }
            else
            {
                send_confirmation(static_cast<storage_result_t>(CMD_MACRO_FAILURE),
                                  session_record.data.max);
            }
        }
        else
        {
            if (++session_record.retry_counter < MAX_NUMBER_OF_RETRY)
            {
                send_indication(session_record.data.index, session_record.data.max);
                session_record.timeout_id = add_alarm_in_ms(RETRY_TIMEOUT_MS, retry_timer_callback, NULL, true);
            }
            else
            {
                send_confirmation(static_cast<storage_result_t>(CMD_MACRO_FAILURE),
                                  session_record.data.max);
                reset_session();
            }
        }
    }
    else
    {
        send_confirmation(static_cast<storage_result_t>(CMD_MACRO_WRONG_MODE),
                          session_record.data.max);
        reset_session();
    }
}
/**
   \brief Repeat response timer callback function
 */
static int64_t retry_timer_callback(alarm_id_t id, void *user_data)
{
    if (session_record.data.index == session_record.data.max)
    {
        reset_session();
    }
    else
    {
        if (++session_record.retry_counter < MAX_NUMBER_OF_RETRY)
        {
            send_indication(session_record.data.index, session_record.data.max);
            session_record.timeout_id = add_alarm_in_ms(RETRY_TIMEOUT_MS, retry_timer_callback, NULL, true);
        }
        else
        {
            send_confirmation(static_cast<storage_result_t>(CMD_MACRO_FAILURE),
                              session_record.data.max);
            reset_session();
        }
    }
    return 0;
}

static void reset_session(void)
{
    session_record.retry_counter = 0;
    session_record.state = SESSION_IDLE;
    storage_stop();
}

static void send_confirmation(storage_result_t _result, uint16_t _max)
{
    cmd_macro_ctrl_msg_t cfm;
    cfm.result = static_cast<cmd_macro_result_t>(_result);
    cfm.max = _max;
    cmd_macro_load_msg_cfm(&cfm);
}

static void send_indication(uint16_t _index, uint16_t _max)
{
    cmd_macro_transport_msg_t ind;
    ind.index = _index;
    ind.max = _max;
    cmd_macro_load_msg_ind(&ind);
}
