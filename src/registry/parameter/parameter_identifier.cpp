/**
 * \file parameter_identifier.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "parameter_identifier.hpp"

namespace registry
{
    namespace parameter
    {
        /**
         * \brief
         *
         * \param _value
         * \return const IDENTIFIER
         */
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
}
