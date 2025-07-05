// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: registry defines module
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "macros.hpp"

namespace registry
{
    static const size_t PARAMETER_BUFFER_SIZE{128};

    enum result_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
        ERROR = common::result::ERROR,
    };
}
