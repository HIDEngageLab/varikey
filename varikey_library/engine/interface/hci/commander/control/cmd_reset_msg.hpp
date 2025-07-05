// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd reset msg module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "macros.hpp"
#include "payload_reset.hpp"

namespace engine::hci::cmd::reset
{
    using content_t = engine::payload::reset::content_t;

    enum class RESULT : uint8_t
    {
        CRITICAL_ERROR = common::result::ERROR, //< initialization failed (hw disabled, safe state)
        FAILURE = common::result::FAILURE,      //< initialization failed
        SUCCESS = common::result::SUCCESS,      //< initialization done

        BACKUP_CREATED = common::result::CUSTOM,          //< no valid maintainer parameter backup
        PARAMETER_MISSED = common::result::CUSTOM + 1,    //< parameter storage dropped
        PARAMETER_RECREATED = common::result::CUSTOM + 2, //< parameter storage (re)created, no maintainer parameter backup available (radio disabled)
        PARAMETER_RESTORED = common::result::CUSTOM + 3,  //< parameter storage (re)created, maintainer parameters restored from backup
        WATCHDOG = common::result::CUSTOM + 4,            //< reboot after watchdog
    };

    struct message_t
    {
        RESULT result;
        content_t content;
        chunk_t value;
    };

    extern void request(chunk_t const *const _chunk, message_t *const _msg);
    extern void confirmation(message_t *const _msg);
    extern void indication(message_t *const _msg);
}
