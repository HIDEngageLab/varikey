// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Parameter management interface
// SPDX-FileType: SOURCE

#pragma once

#include <cstdint>

#include "macros.hpp"
#include "registry_defines.hpp"

namespace registry::parameter
{
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
