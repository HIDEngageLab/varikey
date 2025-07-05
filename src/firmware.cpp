// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Main firmware implementation
// SPDX-FileType: SOURCE

#include "varikey.hpp"

#include "pico/stdlib.h"

int main(void)
{
    // stdio_init_all();
    
    varikey_loop();
    return 0;
}
