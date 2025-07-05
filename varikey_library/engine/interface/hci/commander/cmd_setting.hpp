// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd setting module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"

namespace engine::hci::cmd::setting
{
    extern void identifier_request(chunk_t const *_chunk);
    extern void parameter_request(chunk_t const *_chunk);
}
