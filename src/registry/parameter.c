/**
 * \file parameter.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 *
 * @copyright Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Parameter data base

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <string.h>

#include <hardware/flash.h>
#include <hardware/sync.h>

#include "checksum.h"
#include "chunk.h"
#include "macros.h"
#include "param_backlight.h"
#include "param_display.h"
#include "param_features.h"
#include "param_key.h"
#include "param_maintainer.h"
#include "param_position.h"
#include "param_serial_number.h"
#include "param_user.h"
#include "parameter.h"

#define REGISTRY_OFFSET (FLASH_PAGE_SIZE * 4096)
#define REGISTRY_FLASH_START (XIP_BASE + REGISTRY_OFFSET)
#define REGISTRY_BACKUP_OFFSET (REGISTRY_OFFSET + FLASH_SECTOR_SIZE)
#define REGISTRY_BACKUP_FLASH_START (XIP_BASE + REGISTRY_BACKUP_OFFSET)

#define PARAM_CONTENT_OFFSET 2

/**
    \name Parameter storage (RAM)

    Size:
    Node parameter:     crc:
    backlight   4+4     2       =    10
    display     2+2     2       =     6
    features    1       2       =     3
    key         2+2     2       =     6
    maintainer  1       2       =     3
    position    4+4     2       =    10
    serial      12      2       =    14
    user        2       2       =     4
    -----------------------------------
                                =    50
    CRC-16:
    2                           =     2
    -----------------------------------
    sum:                        =    52
*/

/* @{ */
uint8_t *const registry_start = (uint8_t *)REGISTRY_FLASH_START;

uint8_t *const param_start = registry_start;

uint8_t *const g_param_backlight = param_start;
uint8_t *const g_param_display = (uint8_t *)(g_param_backlight + PARAM_CONTENT_OFFSET + sizeof(param_backlight_t));
uint8_t *const g_param_features = (uint8_t *)(g_param_display + PARAM_CONTENT_OFFSET + sizeof(param_display_t));
uint8_t *const g_param_key = (uint8_t *)(g_param_features + PARAM_CONTENT_OFFSET + sizeof(param_features_t));
uint8_t *const g_param_maintainer = (uint8_t *)(g_param_key + PARAM_CONTENT_OFFSET + sizeof(param_key_t));
uint8_t *const g_param_position = (uint8_t *)(g_param_maintainer + PARAM_CONTENT_OFFSET + sizeof(param_maintainer_t));
uint8_t *const g_param_serial_number = (uint8_t *)(g_param_position + PARAM_CONTENT_OFFSET + sizeof(param_position_t));
uint8_t *const g_param_user = (uint8_t *)(g_param_serial_number + PARAM_CONTENT_OFFSET + sizeof(param_serial_number_t));

uint8_t *const param_crc = (uint8_t *)(g_param_user + PARAM_CONTENT_OFFSET + sizeof(param_user_register_t));
uint8_t *const param_stop = (uint8_t *)(param_crc + sizeof(uint16_t));

/**
    \name Parameter backup (RAM)

    Size: l.u.
*/
/* @} */
uint8_t *const backup_start = (uint8_t *)REGISTRY_BACKUP_FLASH_START;

uint8_t *const backup_backlight = backup_start;
uint8_t *const backup_display = (uint8_t *)(backup_backlight + PARAM_CONTENT_OFFSET + sizeof(param_backlight_t));
uint8_t *const backup_features = (uint8_t *)(backup_display + PARAM_CONTENT_OFFSET + sizeof(param_display_t));
uint8_t *const backup_key = (uint8_t *)(backup_features + PARAM_CONTENT_OFFSET + sizeof(param_features_t));
uint8_t *const backup_maintainer = (uint8_t *)(backup_key + PARAM_CONTENT_OFFSET + sizeof(param_key_t));
uint8_t *const backup_position = (uint8_t *)(backup_maintainer + PARAM_CONTENT_OFFSET + sizeof(param_maintainer_t));
uint8_t *const backup_serial_number = (uint8_t *)(backup_position + PARAM_CONTENT_OFFSET + sizeof(param_position_t));
uint8_t *const backup_user = (uint8_t *)(backup_serial_number + PARAM_CONTENT_OFFSET + sizeof(param_serial_number_t));

uint8_t *const backup_crc = (uint8_t *)(backup_user + PARAM_CONTENT_OFFSET + sizeof(param_user_register_t));
uint8_t *const backup_stop = (uint8_t *)(backup_crc + sizeof(uint16_t));

uint8_t *const registry_stop = backup_stop;
/* @} */

static uint16_t calculate_crc(uint8_t *const _target, size_t _size);
static uint16_t checksum_calculation(const uint8_t *_param, const size_t _size, const uint16_t _result);

static result_t param_save(uint8_t *const _target);

static result_t backlight_store(uint8_t *const _param);
static result_t display_store(uint8_t *const _param);
static result_t features_store(uint8_t *const _param);
static result_t key_store(uint8_t *const _param);
static result_t maintainer_store(uint8_t *const _param);
static result_t position_store(uint8_t *const _param);
static result_t serial_number_store(uint8_t *const _param);
static result_t user_store(uint8_t *const _param);

static result_t backlight_load(uint8_t *const _source);
static result_t display_load(uint8_t *const _source);
static result_t features_load(uint8_t *const _source);
static result_t key_load(uint8_t *const _source);
static result_t maintainer_load(uint8_t *const _source);
static result_t position_load(uint8_t *const _source);
static result_t serial_number_load(uint8_t *const _source);
static result_t user_load(uint8_t *const _source);

#if defined(DEBUG_MEMORY_PRINTOUT)
#include <stdio.h>
extern void debug_out_mem()
{
    size_t size = param_crc - g_param_features + 2;
    // uint32_t size = (uint32_t)(param_crc - g_param_features);
    printf("param  mem (%8d): ", size);
    for (int i = 0; i < size; ++i)
    {
        // printf("%02x ", i);
        printf("%02x ", g_param_features[i]);
        // printf("%02x ", (uint8_t)*(registry_start + i));
    }
    printf("\n");

    size = backup_crc - backup_features + 2;
    printf("backup mem (%8d): ", size);
    for (int i = 0; i < size; ++i)
    {
        // printf("%02x ", i);
        printf("%02x ", backup_features[i]);
    }
    printf("\n");
}
#endif

/**
    \brief Erase a sector with parameter data page and backup page

    Unsafe.
*/
extern result_t param_format(void)
{
    /* clean up memory */
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(REGISTRY_OFFSET, FLASH_SECTOR_SIZE);
    restore_interrupts(ints);

    /* create node parameter */
    param_backlight_init();
    param_display_init();
    param_features_init();
    param_key_init();
    param_maintainer_init();
    param_position_init();
    param_serial_number_init();
    param_user_init();

    return param_save(registry_start);
}

/**
    \brief Calculate and check parameter CRC-16
*/
extern result_t param_check(void)
{
    const uint16_t old_crc_value = SETWORD(param_crc[0], param_crc[1]);
    size_t size = param_crc - param_start;
    const uint16_t new_crc_value = calculate_crc(param_start, size);

    if (old_crc_value == new_crc_value)
    {
        return SUCCESS;
    }
    return FAILURE;
}

/**
    \brief Calculate and check backup CRC-16
*/
extern result_t param_backup_check(void)
{
    const uint16_t old_crc_value = SETWORD(backup_crc[0], backup_crc[1]);
    size_t size = backup_crc - backup_start;
    const uint16_t new_crc_value = calculate_crc(backup_start, size);

    if (old_crc_value == new_crc_value)
    {
        return SUCCESS;
    }
    return FAILURE;
}

/**
    \brief a very, very simple implementation

    store data
*/
extern result_t param_backup_create(void)
{
    /* load node parameter */
    param_backlight_load();
    param_display_load();
    param_features_load();
    param_key_load();
    param_maintainer_load();
    param_position_load();
    param_serial_number_load();
    param_user_load();

    return param_save(backup_start);
}

/**
    \brief a very, very simple implementation

    CRC calculation over the params?
*/
extern result_t param_backup_restore(void)
{
    /* node parameter */
    backlight_load(backup_backlight);
    display_load(backup_display);
    features_load(backup_features);
    key_load(backup_key);
    maintainer_load(backup_maintainer);
    position_load(backup_position);
    serial_number_load(backup_serial_number);
    user_load(backup_user);

    param_save(registry_start);

    /* Check restore process result */
    uint16_t param_crc_value = SETWORD(param_crc[0], param_crc[1]);
    uint16_t backup_crc_value = SETWORD(backup_crc[0], backup_crc[1]);

    if (backup_crc_value == param_crc_value)
    {
        return SUCCESS;
    }
    return FAILURE;
}

/**
    \brief Load features from the persistence memory
*/
extern result_t param_features_load(void)
{
    return features_load(g_param_features);
}

/**
    \brief Store parameter value to the persistence memory
*/
extern result_t param_features_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load maintainer from the persistent memory

    Set proper maintainer value for medium layer identity
*/
extern result_t param_maintainer_load(void)
{
    return maintainer_load(g_param_maintainer);
}

/**
    \brief Store maintainer parameter value to the persistent memory
*/
extern result_t param_maintainer_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load position from the persistence memory
*/
extern result_t param_position_load(void)
{
    return position_load(g_param_position);
}

/**
    \brief Store position to the persistent memory
*/
extern result_t param_position_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load serial number value from the persistence memory
*/
extern result_t param_serial_number_load(void)
{
    return serial_number_load(g_param_serial_number);
}

/**
    \brief Store serial number value to the persistence memory
*/
extern result_t param_serial_number_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load value from the persistence memory
*/
extern result_t param_backlight_load(void)
{
    return backlight_load(g_param_backlight);
}

/**
    \brief Store value to the persistence memory
*/
extern result_t param_backlight_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load value from the persistence memory
*/
extern result_t param_key_load(void)
{
    return key_load(g_param_key);
}

/**
    \brief Store value to the persistence memory
*/
extern result_t param_key_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load value from the persistence memory
*/
extern result_t param_display_load(void)
{
    return key_load(g_param_key);
}

/**
    \brief Store value to the persistence memory
*/
extern result_t param_display_store(void)
{
    return param_save(registry_start);
}

/**
    \brief Load test register from the persistence memory
*/
extern result_t param_user_load(void)
{
    return user_load(g_param_user);
}

/**
    \brief Store parameter value
*/
extern result_t param_user_store(void)
{
    result_t result = param_save(registry_start);
    // debug_out_mem();
    return result;
}

static uint16_t checksum_calculation(const uint8_t *_param, const size_t _size, const uint16_t _result)
{
    uint16_t result = _result;

    for (uint8_t i = 0; i < _size; ++i)
    {
        result = checksum_crc_byte(_param[i], result);
    }
    return result;
}

/**
    \brief CRC-16 calculation
*/
static uint16_t calculate_crc(uint8_t *const _target, size_t _size)
{
    return checksum_calculation(_target, _size, 0);
}

// #include <stdio.h>
static result_t param_save(uint8_t *const _target)
{
    /* read flash page */
    uint8_t data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i)
    {
        data[i] = _target[i];
    }

    uint8_t *data_ptr = data;
    uint8_t *start = data_ptr;

    /* store parameter into the RAM array */
    backlight_store(data_ptr);
    data_ptr += sizeof(param_backlight_t) + PARAM_CONTENT_OFFSET;

    display_store(data_ptr);
    data_ptr += sizeof(param_display_t) + PARAM_CONTENT_OFFSET;

    features_store(data_ptr);
    data_ptr += sizeof(param_features_t) + PARAM_CONTENT_OFFSET;

    key_store(data_ptr);
    data_ptr += sizeof(param_key_t) + PARAM_CONTENT_OFFSET;

    maintainer_store(data_ptr);
    data_ptr += sizeof(param_maintainer_t) + PARAM_CONTENT_OFFSET;

    position_store(data_ptr);
    data_ptr += sizeof(param_position_t) + PARAM_CONTENT_OFFSET;

    serial_number_store(data_ptr);
    data_ptr += sizeof(param_serial_number_t) + PARAM_CONTENT_OFFSET;

    user_store(data_ptr);
    data_ptr += PARAMETER_USER_SIZE + PARAM_CONTENT_OFFSET;

    uint8_t *stop = data_ptr;
    size_t size = stop - start;
    // printf("\ndata mem (%8d): ", size);
    // for (int i = 0; i < size; ++i)
    // {
    //     printf("%02x ", data[i]);
    // }
    uint16_t crc = calculate_crc(data, size);
    // printf("\ncrc:%04x\n", crc);

    *data_ptr = HIBYTE(crc);
    data_ptr++;
    *data_ptr = LOBYTE(crc);
    data_ptr++;
    // {
    //     size_t size = data_ptr - data;
    //     printf("       ram (%8d): ", size);
    //     for (int i = 0; i < size; ++i)
    //     {
    //         printf("%02x ", data[i]);
    //     }
    //     printf("\n");
    // }
    /* store byte to the flash */
    uint32_t offset = (uint32_t)_target - XIP_BASE;

    // printf("offset:%08x address:%08x data:%08x size:%d page:%d\n", offset, _target, data, (data_ptr - data), FLASH_PAGE_SIZE);
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(offset, FLASH_SECTOR_SIZE);
    flash_range_program(offset, data, FLASH_PAGE_SIZE);
    restore_interrupts(ints);

    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i)
    {
        if (data[i] != _target[i])
        {
            mismatch = true;
        }
    }

    if (mismatch == true)
    {
        // printf("failure\n");
        return FAILURE;
    }

    return SUCCESS;
}

static result_t backlight_store(uint8_t *const _param)
{
    /* store control information */
    _param[0] = PARAMETER_IDENTIFIER_BACKLIGHT;
    _param[1] = sizeof(param_backlight_t);

    /* store latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_backlight_t); ++i)
    {
        _param[2 + i] = g_backlight.byte[i];
    }

    return SUCCESS;
}

static result_t display_store(uint8_t *const _param)
{
    /* store control information */
    _param[0] = PARAMETER_IDENTIFIER_DISPLAY;
    _param[1] = sizeof(param_display_t);

    /* store display parameter */
    for (uint8_t i = 0; i < sizeof(param_display_t); ++i)
    {
        _param[2 + i] = g_display.byte[i];
    }

    return SUCCESS;
}

static result_t features_store(uint8_t *const _param)
{
    /* store parameter infos */
    _param[0] = PARAMETER_IDENTIFIER_FEATURES;
    _param[1] = sizeof(param_features_t);

    /* store parameter value to the persistence memory */
    _param[2] = g_features.byte;

    return SUCCESS;
}

static result_t maintainer_store(uint8_t *const _param)
{
    /* store parameter value */
    _param[0] = PARAMETER_IDENTIFIER_MAINTAINER;
    _param[1] = sizeof(param_maintainer_t);

    _param[2] = g_maintainer.byte;

    return SUCCESS;
}

static result_t position_store(uint8_t *const _param)
{
    /* store control information */
    _param[0] = PARAMETER_IDENTIFIER_POSITION;
    _param[1] = sizeof(param_position_t);

    /* store latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_position_t); ++i)
    {
        _param[2 + i] = g_position.byte[i];
    }

    return SUCCESS;
}

static result_t serial_number_store(uint8_t *const _param)
{
    /* deserialize parameter value */
    _param[0] = PARAMETER_IDENTIFIER_SERIAL_NUMBER;
    _param[1] = PARAMETER_SERIAL_NUMBER_SIZE;

    for (uint8_t i = 0; i < PARAMETER_SERIAL_NUMBER_SIZE; ++i)
    {
        _param[2 + i] = g_serial_number.value[i];
    }

    return SUCCESS;
}

static result_t key_store(uint8_t *const _param)
{
    /* store control information */
    _param[0] = PARAMETER_IDENTIFIER_KEY;
    _param[1] = sizeof(param_key_t);

    /* store latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_key_t); ++i)
    {
        _param[2 + i] = g_key.byte[i];
    }

    return SUCCESS;
}

static result_t user_store(uint8_t *const _param)
{
    /* store test register */
    _param[0] = PARAMETER_IDENTIFIER_USER;
    _param[1] = PARAMETER_USER_SIZE;

    _param[2] = g_user_register.value[0];
    _param[3] = g_user_register.value[1];

    return SUCCESS;
}

static result_t backlight_load(uint8_t *const _source)
{
    /* check for plausibility */
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    if (identifier != PARAMETER_IDENTIFIER_BACKLIGHT || length != sizeof(param_backlight_t))
    {
        param_backlight_init();
        return FAILURE;
    }

    /* set default values */
    param_backlight_init();

    /* load latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_backlight_t); ++i)
    {
        g_backlight.byte[i] = _source[2 + i];
    }

    return SUCCESS;
}

static result_t display_load(uint8_t *const _source)
{
    /* check for plausibility */
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    if (identifier != PARAMETER_IDENTIFIER_DISPLAY || length != sizeof(param_display_t))
    {
        param_backlight_init();
        return FAILURE;
    }

    /* set default values */
    param_backlight_init();

    /* load latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_display_t); ++i)
    {
        g_display.byte[i] = _source[2 + i];
    }

    return SUCCESS;
}

static result_t features_load(uint8_t *const _source)
{
    const uint8_t identifier = _source[0];
    const uint8_t length = _source[1];

    /* check for plausibility */
    if (identifier != PARAMETER_IDENTIFIER_FEATURES || length != sizeof(param_features_t))
    {
        /* set default values */
        param_features_init();
        return FAILURE;
    }

    /* load features */
    g_features.byte = _source[2];

    return SUCCESS;
}

static result_t key_load(uint8_t *const _source)
{
    /* check for plausibility */
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    if (identifier != PARAMETER_IDENTIFIER_KEY || length != sizeof(param_key_t))
    {
        param_key_init();
        return FAILURE;
    }

    /* set default values */
    param_key_init();

    /* load latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_key_t); ++i)
    {
        g_key.byte[i] = _source[2 + i];
    }

    return SUCCESS;
}

static result_t maintainer_load(uint8_t *const _source)
{
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    /* check for plausibility */
    if (identifier != PARAMETER_IDENTIFIER_MAINTAINER || length != sizeof(param_maintainer_t))
    {
        param_maintainer_init();
        return FAILURE;
    }

    /* set default values */
    param_maintainer_init();

    /* load maintainer */
    g_maintainer.byte = _source[2];

    return SUCCESS;
}

static result_t position_load(uint8_t *const _source)
{
    /* check for plausibility */
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    if (identifier != PARAMETER_IDENTIFIER_POSITION || length != sizeof(param_position_t))
    {
        param_position_init();
        return FAILURE;
    }

    /* set default values */
    param_position_init();

    /* load latitude and longitude */
    for (uint8_t i = 0; i < sizeof(param_position_t); ++i)
    {
        g_position.byte[i] = _source[2 + i];
    }

    return SUCCESS;
}

static result_t serial_number_load(uint8_t *const _source)
{
    /* check for plausibility */
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    /* load parameter value */
    for (uint8_t i = 0; i < PARAMETER_SERIAL_NUMBER_SIZE; ++i)
    {
        g_serial_number.value[i] = _source[2 + i];
    }

    g_unique_key = SETLONG(SETWORD(g_serial_number.value[PARAMETER_SERIAL_NUMBER_SIZE - 4],
                                   g_serial_number.value[PARAMETER_SERIAL_NUMBER_SIZE - 3]),
                           SETWORD(g_serial_number.value[PARAMETER_SERIAL_NUMBER_SIZE - 2],
                                   g_serial_number.value[PARAMETER_SERIAL_NUMBER_SIZE - 1]));

    /*  check plausibility: 1) wrong identifier or length, 2) empty the persistence memory */
    if (identifier != PARAMETER_IDENTIFIER_SERIAL_NUMBER || length != PARAMETER_SERIAL_NUMBER_SIZE || g_unique_key == KEY_VALUE_INVALID)
    {
        /* serial number is not valid => create new one */
        param_serial_number_init();
        return FAILURE;
    }

    return SUCCESS;
}

static result_t user_load(uint8_t *const _source)
{
    uint8_t identifier = _source[0];
    uint8_t length = _source[1];

    /* check for plausibility */
    if (identifier != PARAMETER_IDENTIFIER_USER || length != PARAMETER_USER_SIZE)
    {
        param_user_init();
        return FAILURE;
    }

    /* load test register */
    g_user_register.value[0] = _source[2];
    g_user_register.value[1] = _source[3];

    return SUCCESS;
}
