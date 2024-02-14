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

namespace engine
{
    extern void initialize(void);
    extern void shutdown(void);

    extern void perform(void);

    extern void start(void);
    extern void stop(void);

    extern void unmount();
    extern void mount();
    extern void suspend(const bool wakeup_enabled);
    extern void resume();

    extern defines::STATE get_mode(void);
}

#endif /* __ENGINE_HPP__ */
