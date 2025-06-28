/**
 * \file varikey.c
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "varikey.hpp"

#include "pico/stdlib.h"

int main(void)
{
    // stdio_init_all();
    
    varikey_loop();
    return 0;
}
