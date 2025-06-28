/**
 * \file hid_report.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <string>

#include "board_assembly.hpp"
#include "hid_report.hpp"

namespace engine
{
    namespace hid
    {
        void set_report_t::deserialize(const const_chunk_t &_buffer)
        {
            assert(_buffer.size <= MAX_REPORT_SIZE);

            report = static_cast<SET_REPORT>(_buffer.space[0]);
            memcpy((void *)buffer, (void *)&_buffer.space[1], _buffer.size - 1);
        }

        void set_report_t::serialize(const chunk_t &_buffer) const
        {
            assert(_buffer.size <= MAX_REPORT_SIZE);

            _buffer.space[0] = static_cast<const uint8_t>(report);
            memcpy((void *)&_buffer.space[1], (void *)buffer, _buffer.size - 1);
        }
    }
}
