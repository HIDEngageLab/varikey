// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: cmd control module
// SPDX-FileType: SOURCE

#pragma once

#include "chunk.h"
#include "cmd_reset_msg.hpp"
#include "engine_defines.hpp"

namespace engine::hci::cmd::control
{
    extern void gadget_indication(engine::defines::STATE const);
    extern void gadget_request(chunk_t const *const);
    extern void hash_request(chunk_t const *const);
    extern void reset_indication(hci::cmd::reset::RESULT const);
    extern void reset_request(chunk_t const *const);
    extern void temperature_request(chunk_t const *const);
}
