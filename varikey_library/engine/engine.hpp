// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Main engine interface
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "engine_defines.hpp"

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
}
