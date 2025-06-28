/**
 * \file component_interface.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PULP_COMPONENT_INTERFACE_HPP__
#define __PULP_COMPONENT_INTERFACE_HPP__

namespace pulp
{
    struct ComponentInterface
    {
        virtual ~ComponentInterface() {}

        virtual void initialize() = 0;
        virtual void shutdown() = 0;
    };
}

#endif // __PULP_COMPONENT_INTERFACE_HPP__
