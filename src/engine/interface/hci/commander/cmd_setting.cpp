/**
 * \file cmd_setting.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Module configuration

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "cmd_setting.hpp"
#include "cmd_identity_msg.hpp"
#include "cmd_parameter_msg.hpp"
#include "param_backlight.hpp"
#include "param_display.hpp"
#include "param_features.hpp"
#include "param_keypad.hpp"
#include "param_maintainer.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_user.hpp"
#include "payload_parameter.hpp"
#include "registry_interface.hpp"
#include "varikey.hpp"

namespace engine
{
    namespace hci
    {
        namespace cmd
        {
            namespace setting
            {
                static const size_t PARAMETER_BUFFER_SIZE{100};

                /**
                    \brief Module Identifier Request

                    Sends a part of a firmware, hardware and module identifier in a confirmation message
                */
                extern void identifier_request(chunk_t const *_chunk)
                {
                    identity::message_t msg;
                    identity::request(_chunk, &msg);
                    identity::confirmation(&msg);
                }

                /**
                    \brief Parameter request

                    Set or get a module configuration parameter
                */
                extern void parameter_request(chunk_t const *_chunk)
                {
                    param::message_t msg;

                    uint8_t space[PARAMETER_BUFFER_SIZE];
                    msg.value.size = PARAMETER_BUFFER_SIZE;
                    msg.value.space = space;

                    param::request(_chunk, &msg);
                    param::confirmation(&msg);
                }
            }
        }
    }
}