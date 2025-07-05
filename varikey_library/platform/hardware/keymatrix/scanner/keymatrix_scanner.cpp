// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Hardware keymatrix scanner functionality
// SPDX-FileType: SOURCE

#include "keymatrix_scanner.hpp"

namespace platform::hardware
{
    void KeymatrixScanner::initialize()
    {
        pulp::ComponentInterface::initialize();
    }

    void KeymatrixScanner::shutdown()
    {
        pulp::ComponentInterface::shutdown();
    }

    bool KeymatrixScanner::perform(void)
    {
    }
}