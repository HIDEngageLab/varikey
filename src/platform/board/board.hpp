/**
 * \file board.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BOARD_HPP__
#define __PLATFORM_BOARD_HPP__

#include "board_type.hpp"

extern void board_initialize();
extern void board_shutdown();
extern void board_perform();

extern platform::Board board;

#endif // __PLATFORM_BOARD_HPP__
