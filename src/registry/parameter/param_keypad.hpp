/**
 * \file param_keypad.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * \copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "keypad"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAM_KEYPAD_HPP__
#define __PARAM_KEYPAD_HPP__

#include "parameter.hpp"

namespace registry
{
    namespace parameter
    {
        namespace keypad
        {
            /** \brief Node keypad details */
            struct keypad_t
            {
                uint16_t click_ms;
                uint16_t push_ms;
            } __attribute__((packed));

            static const size_t SIZE = sizeof(keypad_t);
            /**
                \brief Keypad parameter

                Parameter with two short values for keypad click and push times in ms.
            */
            union register_t
            {
                uint8_t byte[SIZE];
                keypad_t value;

                void initialize(void);

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            } __attribute__((packed));

            extern register_t g_register;
        }
    }
}

#endif /* __PARAM_KEYPAD_HPP__ */
