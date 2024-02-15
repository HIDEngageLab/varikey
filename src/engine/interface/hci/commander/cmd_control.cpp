/**
 * \file cmd_control.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module control

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <stddef.h>
#include <stdlib.h>

#include <hardware/watchdog.h>

#include "cmd_control.hpp"
#include "cmd_gadget_msg.hpp"
#include "cmd_hash_msg.hpp"
#include "cmd_reset_msg.hpp"
#include "cmd_temperature_msg.hpp"
#include "commander.hpp"
#include "engine_event.hpp"
#include "engine_event_handler.hpp"
#include "keypad.hpp"
#include "parameter.hpp"
#include "serial_frame.hpp"
#include "usart.hpp"
#include "varikey.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace control
            {
                /**
                    \brief Handle status request
                */
                extern void gadget_request(chunk_t const *const _chunk)
                {
                    gadget::message_t msg;
                    gadget::request(_chunk, &msg);
                    gadget::confirmation(&msg);
                }

                /**
                    \brief Handle key request
                */
                extern void hash_request(chunk_t const *const _chunk)
                {
                    hash::message_t msg;
                    hash::request(_chunk, &msg);
                    hash::confirmation(&msg);
                }

                /**
                    \brief Send a state switch indication message
                */
                extern void protocol_indication(defines::STATE const _mode)
                {
                    gadget::message_t msg;
                    msg.gadget.command = payload::gadget::COMMAND::GET;

                    switch (_mode)
                    {
                    case defines::STATE::ACTIVE:
                        msg.gadget.mode = payload::gadget::MODE::ACTIVE;
                        break;
                    case defines::STATE::IDLE:
                        msg.gadget.mode = payload::gadget::MODE::IDLE;
                        break;
                    case defines::STATE::PENDING:
                        msg.gadget.mode = payload::gadget::MODE::PENDING;
                        break;
                    case defines::STATE::UNDEFINED:
                    default:
                        msg.gadget.mode = payload::gadget::MODE::UNDEFINED;
                        break;
                    }
                    gadget::indication(&msg);
                }

                /**
                    \brief Handle reset request
                */
                extern void reset_request(chunk_t const *const _chunk)
                {
                    reset::message_t msg;
                    reset::request(_chunk, &msg);

                    const handler::event_t event = {
                        .identifier = payload::IDENTIFIER::RESET,
                        .reset = {
                            .function = msg.content.function,
                        },
                    };
                    handler::event_queue.push(event);
                }

                /**
                    \brief Handle reset indication
                */
                extern void reset_indication(hci::cmd::reset::RESULT const _result)
                {
                    reset::message_t msg;
                    msg.content.function = engine::payload::reset::FUNCTION::SHUTDOWN;
                    msg.result = _result;
                    reset::indication(&msg);
                }

                /**
                    \brief Handle temperature request
                */
                extern void temperature_request(chunk_t const *const _chunk)
                {
                    temperature::message_t msg;
                    temperature::request(_chunk, &msg);
                    temperature::confirmation(&msg);
                }

            }
        }
    }
}
