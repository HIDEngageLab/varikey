/**
 * \file parameter.h
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief Configuration parameter storage

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <stdint.h>

#include "types.h"

/**
    \brief Parameter identifier type
*/
typedef enum
{
    PARAMETER_IDENTIFIER_BACKLIGHT = 0xA1,
    PARAMETER_IDENTIFIER_DISPLAY = 0xA3,
    PARAMETER_IDENTIFIER_FEATURES = 0x51,
    PARAMETER_IDENTIFIER_KEY = 0xA2,
    PARAMETER_IDENTIFIER_MAINTAINER = 0x23,
    PARAMETER_IDENTIFIER_POSITION = 0x24,
    PARAMETER_IDENTIFIER_SERIAL_NUMBER = 0x11,
    PARAMETER_IDENTIFIER_USER = 0x70,
} param_identifier_t;

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

extern result_t param_key_load(void);
extern result_t param_key_store(void);

extern result_t param_maintainer_load(void);
extern result_t param_maintainer_store(void);

extern result_t param_position_load(void);
extern result_t param_position_store(void);

extern result_t param_serial_number_load(void);
extern result_t param_serial_number_store(void);

extern result_t param_user_load(void);
extern result_t param_user_store(void);

extern void debug_out_mem();

#endif /* __PARAMETER_H__ */
