// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: hid handler module
// SPDX-FileType: SOURCE

#pragma once

#include "hid_report.hpp"

namespace engine::hid
{
    extern void set_report_handler(const uint8_t, const const_chunk_t &);
    extern void get_report_handler(const uint8_t, const chunk_t &);
}
