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
#include "component_state.hpp"

extern void engine_initialize(void);
extern void engine_shutdown(void);

extern void engine_perform(void);

extern void engine_start(void);
extern void engine_stop(void);

extern void engine_tick(void);

extern pulp::COMPONENT_STATE engine_mode_get(void);

#endif /* __ENGINE_HPP__ */
