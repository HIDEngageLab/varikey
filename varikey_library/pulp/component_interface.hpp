// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Component interface definition
// SPDX-FileType: SOURCE

#pragma once

namespace pulp
{
    struct ComponentInterface
    {
        virtual ~ComponentInterface() {}

        virtual void initialize() = 0;
        virtual void shutdown() = 0;
    };
}
