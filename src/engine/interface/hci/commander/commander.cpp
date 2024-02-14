/**
 * \file commander.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Command interpreter on the host interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <assert.h>
#include <stddef.h>

#include "cmd_control.hpp"
#include "cmd_feature.hpp"
#include "cmd_setting.hpp"
#include "commander.hpp"
#include "macros.hpp"

namespace engine
{
    namespace hci
    {
        /**
            \brief Interpreter for commander commandos

            This function needs to be registered with register_handler() on the serial frame module.
        */
        extern cmd::protocol::RESULT interpreter(chunk_t const *const _chunk)
        {
            assert(_chunk != NULL); // serial commander interpreter chunk null

            cmd::protocol::RESULT result = cmd::protocol::RESULT::SUCCESS;

            /* command switch */
            const COMMAND command = static_cast<COMMAND>(_chunk->space[0]);
            chunk_t sdu = {&_chunk->space[1], _chunk->size - 1};

            switch (command)
            {
            /* control keypad state */
            case COMMAND::GADGET_REQ:
                cmd::control::gadget_request(&sdu);
                break;

            /* key storage service */
            case COMMAND::HASH_REQ:
                cmd::control::hash_request(&sdu);
                break;

            /* module restart */
            case COMMAND::RESET_REQ:
                cmd::control::reset_request(&sdu);
                break;

            /* check temperature value */
            case COMMAND::TEMPERATURE_REQ:
                cmd::control::temperature_request(&sdu);
                break;

            /* backlight engine service */
            case COMMAND::BACKLIGHT_REQ:
                cmd::feature::backlight_request(&sdu);
                break;

            /* display engine service */
            case COMMAND::DISPLAY_REQ:
                cmd::feature::display_request(&sdu);
                break;

            /* gpio control */
            case COMMAND::GPIO_REQ:
                cmd::feature::gpio_request(&sdu);
                break;

            /* button event handling */
            case COMMAND::KEYPAD_REQ:
                cmd::feature::keypad_request(&sdu);
                break;

            /* check firmware, hardware and module identifier */
            case COMMAND::IDENTITY_REQ:
                cmd::setting::identifier_request(&sdu);
                break;

            /* handle parameter request */
            case COMMAND::PARAM_REQ:
                cmd::setting::parameter_request(&sdu);
                break;

            default:
                /* unknown message */
                result = cmd::protocol::RESULT::INVALID_COMMAND;
                break;
            }

            return result;
        }
    }
}
