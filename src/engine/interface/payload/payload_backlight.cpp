/**
 * \file payload_backlight.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "payload_backlight.hpp"

using namespace engine::payload::backlight;

static const size_t CFM_CMD_SIZE = 1;
static const size_t CFM_CLR_SIZE = CFM_CMD_SIZE + sizeof(uint8_t) * 6;

const size_t content_t::size() const
{
    if (program == PROGRAM::MORPH ||
        program == PROGRAM::SET)
    {
        return CFM_CLR_SIZE;
    }
    return CFM_CMD_SIZE;
}

void content_t::deserialize(uint8_t const *const _space)
{
    program = static_cast<const PROGRAM>(_space[0]);
    if (!(program == PROGRAM::ALERT ||
          program == PROGRAM::CONST ||
          program == PROGRAM::MEDIUM ||
          program == PROGRAM::MORPH ||
          program == PROGRAM::MOUNT ||
          program == PROGRAM::OFF ||
          program == PROGRAM::SET ||
          program == PROGRAM::SLOW ||
          program == PROGRAM::SUSPEND ||
          program == PROGRAM::TURBO))
    {
        program = PROGRAM::UNDEFINED;
    }
    else if (program == PROGRAM::MORPH ||
             program == PROGRAM::SET)
    {
        left.rgb.r = _space[1];
        left.rgb.g = _space[2];
        left.rgb.b = _space[3];
        right.rgb.r = _space[4];
        right.rgb.g = _space[5];
        right.rgb.b = _space[6];
    }
}

void content_t::serialize(uint8_t **_ptr) const
{
    *(*_ptr)++ = (uint8_t)program;
    if (program == PROGRAM::MORPH ||
        program == PROGRAM::SET)
    {
        *(*_ptr)++ = (uint8_t)left.rgb.r;
        *(*_ptr)++ = (uint8_t)left.rgb.g;
        *(*_ptr)++ = (uint8_t)left.rgb.b;
        *(*_ptr)++ = (uint8_t)right.rgb.r;
        *(*_ptr)++ = (uint8_t)right.rgb.g;
        *(*_ptr)++ = (uint8_t)right.rgb.b;
    }
}
