/**
 * \file engine_defines_varikey.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_DEFINES_VARIKEY_HPP__
#define __ENGINE_DEFINES_VARIKEY_HPP__

#include <cstdint>

namespace engine
{
    namespace defines
    {
        struct Varikey
        {
            static const bool ENABLE_SERAIL_INTERFACE_ON_START = true;
            static const bool ENABLE_USB_INTERFACE_ON_START = true;
        };
    }

}

#endif // __ENGINE_DEFINES_HPP__
