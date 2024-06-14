/**
 * \file engine.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "chunk.h"
#include "engine_defines.hpp"
#include "registry_notify_interface.hpp"

namespace engine
{
    extern void initialize(void);
    extern void shutdown(void);

    extern void perform(void);

    extern void start(void);
    extern void stop(void);

    extern void mount();
    extern void unmount();
    extern void suspend(const bool wakeup_enabled);
    extern void resume();

    extern defines::STATE get_state(void);

    namespace notify
    {
        struct RegistryNotifier : public registry::notify::Notifier
        {
            virtual void send(const registry::notify::Event &) const;
        };

    }
    extern notify::RegistryNotifier registry_notifier;

}

#endif /* __ENGINE_HPP__ */
