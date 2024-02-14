/**
 * \file parameter.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter storage

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <stdint.h>

#include "macros.hpp"
#include "registry_defines.hpp"

namespace registry
{
    namespace parameter
    {
        /**
            \brief Parameter identifier type
        */
        enum class IDENTIFIER : uint8_t
        {
            BACKLIGHT = 0xA1,
            DISPLAY = 0xA3,
            FEATURES = 0x51,
            KEYPAD = 0xA2,
            MAINTAINER = 0x23,
            MAPPING = 0xB0,
            POSITION = 0x24,
            SERIAL_NUMBER = 0x11,
            UNDEFINED = 0xff,
            USER = 0x70,
        };

        extern const IDENTIFIER to_identifier(const uint8_t);

        extern result_t param_format(void);
        extern result_t param_check(void);

        extern result_t param_backup_check(void);
        extern result_t param_backup_create(void);
        extern result_t param_backup_restore(void);

        extern result_t param_backlight_load(void);
        extern result_t param_backlight_store(void);

        extern result_t param_display_load(void);
        extern result_t param_display_store(void);

        extern result_t param_features_load(void);
        extern result_t param_features_store(void);

        extern result_t param_keypad_load(void);
        extern result_t param_keypad_store(void);

        extern result_t param_maintainer_load(void);
        extern result_t param_maintainer_store(void);

        extern result_t param_mapping_load(void);
        extern result_t param_mapping_store(void);

        extern result_t param_position_load(void);
        extern result_t param_position_store(void);

        extern result_t param_serial_number_load(void);
        extern result_t param_serial_number_store(void);

        extern result_t param_user_load(void);
        extern result_t param_user_store(void);

        extern void debug_out_mem();

    }
}

#endif /* __PARAMETER_HPP__ */
