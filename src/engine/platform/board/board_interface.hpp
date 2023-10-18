/**
 * \file board_interface.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_INTERFACE_H__
#define __PLATFORM_INTERFACE_H__

namespace platform
{
    namespace board
    {
        struct Interface
        {
            virtual ~Interface() {}
            const virtual int getIdentifier() const = 0;
        };
    }
}

#endif /* __PLATFORM_INTERFACE_H__ */
