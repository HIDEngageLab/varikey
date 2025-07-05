// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware keymatrix functionality
// SPDX-FileType: SOURCE

#pragma once

#include <cstdbool>
#include <cstdint>

#include "pico/stdlib.h"

void keymatrix_init(void);
void keymatrix_scan(void);
void keymatrix_events(void);
