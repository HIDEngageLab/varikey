/**
 * \file cmd_gadget_msg.cpp
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

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "cmd_gadget_msg.hpp"
#include "commander.hpp"
#include "component_state.hpp"
#include "engine.hpp"
#include "engine_defines.hpp"
#include "macros.hpp"
#include "param_features.hpp"
#include "param_serial_number.hpp"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace gadget
            {

                static const size_t CFM_SIZE = 8;
                static const size_t IND_SIZE = 7;

                /**
                    \brief Status request message

                    Deserialize only.
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    assert(_chunk != NULL && _msg != NULL); // chunk is not null

                    /* deserialize */
                    _msg->result = RESULT::FAILURE;

                    _msg->gadget.deserialize(_chunk->space);

                    const defines::STATE mode = get_mode();
                    switch (mode)
                    {
                    case defines::STATE::IDLE:
                        _msg->gadget.state = payload::gadget::STATE::IDLE;
                        break;

                    case defines::STATE::ACTIVE:
                        _msg->gadget.state = payload::gadget::STATE::ACTIVE;
                        break;

                    case defines::STATE::PENDING:
                        _msg->gadget.state = payload::gadget::STATE::PENDING;
                        break;

                    default:
                        _msg->gadget.state = payload::gadget::STATE::UNDEFINED;
                        break;
                    }

                    _msg->value.size = _chunk->size - 1;
                    _msg->value.space = &_chunk->space[1];

                    /* trigger status/operation event */
                    if (_msg->gadget.function == payload::gadget::FUNCTION::GET)
                    {
                        _msg->result = RESULT::SUCCESS;
                    }
                    else
                    {
                        switch (_msg->gadget.function)
                        {
                        case payload::gadget::FUNCTION::MOUNT:
                            if (mode == defines::STATE::IDLE)
                            {
                                engine::mount();
                                _msg->result = RESULT::SUCCESS;
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_STATE;
                            }
                            break;
                        case payload::gadget::FUNCTION::UNMOUNT:
                            if (mode == defines::STATE::ACTIVE ||
                                mode == defines::STATE::PENDING)
                            {
                                engine::unmount();
                                _msg->result = RESULT::SUCCESS;
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_STATE;
                            }
                            break;
                        case payload::gadget::FUNCTION::SUSPEND:
                            if (mode == defines::STATE::ACTIVE ||
                                mode == defines::STATE::IDLE)
                            {
                                engine::suspend(registry::parameter::features::g_register.value.wakeup);
                                _msg->result = RESULT::SUCCESS;
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_STATE;
                            }
                            break;
                        case payload::gadget::FUNCTION::RESUME:
                            if (mode == defines::STATE::SUSPEND)
                            {
                                engine::resume();
                                _msg->result = RESULT::SUCCESS;
                            }
                            else
                            {
                                _msg->result = RESULT::WRONG_STATE;
                            }
                            break;
                        default:
                            _msg->result = RESULT::UNKNOWN;
                            break;
                        }
                    }
                }

                /**
                    \brief Send status confirmation
                */
                extern void confirmation(message_t *const _msg)
                {
                    assert(_msg != NULL); // command control status confirmation message not null

                    /* space */
                    uint8_t space[CFM_SIZE] = {0};
                    _msg->value.size = CFM_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::GADGET_CFM;
                    *ptr++ = (uint8_t)_msg->result;

                    _msg->gadget.serialize(&ptr);

                    serialize_long(registry::parameter::serial_number::g_unique_key, &ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }

                /**
                    \brief Send status indication
                */
                extern void indication(message_t *const _msg)
                {
                    assert(_msg != NULL); // command control status indication message not null

                    /* handle */
                    uint8_t space[IND_SIZE] = {0};
                    _msg->value.size = IND_SIZE;
                    _msg->value.space = space;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::GADGET_IND;

                    _msg->gadget.serialize(&ptr);

                    serialize_long(registry::parameter::serial_number::g_unique_key, &ptr);

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}