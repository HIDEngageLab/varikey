/**
 * \file registry_notify_interface.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

#include "macros.hpp"

namespace registry
{
    namespace notify
    {
        enum class EVENT_CAUSE : uint8_t
        {
            RESET,
            UNDEFINED = 0xff,
        };

        enum class EVENT_IDENTIFIER: uint8_t
        {
            BACKUP_CREATED,
            CRITICAL_ERROR,
            PARAMETER_MISSED,

            UNDEFINED = 0xff,
        };

        struct Event
        {
            EVENT_CAUSE cause;
            EVENT_IDENTIFIER identifier;
        };

        struct Notifier
        {
            virtual void send(const Event &) const = 0;
        };
    }
}