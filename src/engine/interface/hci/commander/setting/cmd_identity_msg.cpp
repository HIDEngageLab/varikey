/**
 * \file cmd_identity_msg.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Identifier message

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "array_length.hpp"
#include "chunk.h"
#include "cmd_identity_msg.hpp"
#include "commander.hpp"
#include "macros.hpp"
#include "param_maintainer.hpp"
#include "param_serial_number.hpp"
#include "revision.h"
#include "serial_frame.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace identity
            {
                /**
                    \brief Identity request

                    Deserialize only.
                */
                extern void request(chunk_t const *const _chunk, message_t *const _msg)
                {
                    assert(_chunk != NULL && _msg != NULL); /* identity param request chunk null */
                    /* handle */
                    _msg->identity.deserialize(_chunk->space);

                    if (_msg->identity.identifier == engine::payload::identity::IDENTIFIER::FIRMWARE ||
                        _msg->identity.identifier == engine::payload::identity::IDENTIFIER::HARDWARE ||
                        _msg->identity.identifier == engine::payload::identity::IDENTIFIER::PRODUCT ||
                        _msg->identity.identifier == engine::payload::identity::IDENTIFIER::SERIAL ||
                        _msg->identity.identifier == engine::payload::identity::IDENTIFIER::UNIQUE ||
                        _msg->identity.identifier == engine::payload::identity::IDENTIFIER::PLATFORM)
                    {
                        _msg->result = RESULT::SUCCESS;
                    }
                    else
                    {
                        _msg->result = RESULT::UNSUPPORTED;
                    }

                    _msg->value.size = 0;
                    _msg->value.space = nullptr;
                }

                /**
                    \brief Send Identity confirmation

                    Identities:
                    - Serial number
                    - Platform identifier (maintainer and hw revision)
                */
                extern void confirmation(message_t *const _msg)
                {
                    assert(_msg != NULL); // identity confirmation message null

                    static constexpr std::size_t CFM_SIZE = string_length(::identity::firmware::PRODUCT) +
                                                            string_length(::identity::hardware::PLATFORM) + 1;

                    /*  space for message chunk */
                    uint8_t space[CFM_SIZE] = {0};
                    _msg->value.space = space;
                    _msg->value.size = CFM_SIZE;
                    uint8_t *ptr = space;

                    *ptr++ = (uint8_t)engine::hci::COMMAND::IDENTITY_CFM;
                    *ptr++ = (uint8_t)_msg->result;

                    _msg->identity.serialize(ptr);
                    _msg->value.size += _msg->identity.size();

                    serial::frame::send(engine::hci::INTERPRETER_ADDRESS, &_msg->value);
                }
            }
        }
    }
}