// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Chunk data structure definitions
// SPDX-FileType: SOURCE

#pragma once

#include <stdint.h>
#include <stdlib.h>

struct chunk_t
{
	uint8_t *space;
	size_t size;
};

struct const_chunk_t
{
	uint8_t const *space;
	size_t size;
};
