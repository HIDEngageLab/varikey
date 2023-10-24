/**
 * \file board.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "board.hpp"

platform::Board board;

extern void board_initialize()
{
    board.initialize();
}

extern void board_shutdown()
{
    board.shutdown();
}

extern void board_perform()
{
    board.perform();

}