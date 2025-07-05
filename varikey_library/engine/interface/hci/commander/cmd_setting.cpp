// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd setting module
// SPDX-FileType: SOURCE

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

namespace engine::hci::cmd::setting
{
    static const size_t PARAMETER_BUFFER_SIZE{registry::PARAMETER_BUFFER_SIZE};

    extern void identifier_request(chunk_t const *_chunk)
    {
        identity::message_t msg;
        identity::request(_chunk, &msg);
        identity::confirmation(&msg);
    }

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