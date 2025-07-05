// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Random number generation utilities
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"

extern void random_init(void);
extern void random_create_sequence(chunk_t *const _sequence);
