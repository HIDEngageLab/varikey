/**
 * \file registry_defines.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __REGISTRY_DEFINES_HPP__
#define __REGISTRY_DEFINES_HPP__

#include "macros.hpp"

namespace registry
{
    enum result_t
    {
        SUCCESS = common::result::SUCCESS,
        FAILURE = common::result::FAILURE,
        ERROR = common::result::ERROR,
    };
}

#endif // __REGISTRY_DEFINES_HPP__
