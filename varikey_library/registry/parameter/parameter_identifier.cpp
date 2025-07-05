// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Parameter identifier implementation
// SPDX-FileType: SOURCE

#include "parameter_identifier.hpp"

namespace registry::parameter
{
    extern const IDENTIFIER to_identifier(const uint8_t _value)
    {
        IDENTIFIER tmp = static_cast<IDENTIFIER>(_value);
        if (tmp == IDENTIFIER::BACKLIGHT ||
            tmp == IDENTIFIER::DISPLAY ||
            tmp == IDENTIFIER::FEATURES ||
            tmp == IDENTIFIER::KEYPAD ||
            tmp == IDENTIFIER::MAINTAINER ||
            tmp == IDENTIFIER::MAPPING ||
            tmp == IDENTIFIER::POSITION ||
            tmp == IDENTIFIER::SERIAL_NUMBER ||
            tmp == IDENTIFIER::USER)
        {
            return tmp;
        }

        return IDENTIFIER::UNDEFINED;
    }
}