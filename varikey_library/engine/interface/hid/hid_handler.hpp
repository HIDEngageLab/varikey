/**
 * \file hid_handler.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_HANDLER_HPP__
#define __ENGINE_HANDLER_HPP__

#include "hid_report.hpp"

namespace engine
{
    namespace hid
    {
        extern void set_report_handler(const uint8_t, const const_chunk_t &);
        extern void get_report_handler(const uint8_t, const chunk_t &);
    }
}

#endif // __ENGINE_HANDLER_HPP__
