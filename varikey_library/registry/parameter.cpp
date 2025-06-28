/**
 * \file parameter.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter data base

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include <string.h>

#include <hardware/flash.h>
#include <hardware/sync.h>

#include "checksum.hpp"
#include "chunk.h"
#include "macros.hpp"
#include "param_backlight.hpp"
#include "param_display.hpp"
#include "param_features.hpp"
#include "param_keypad.hpp"
#include "param_maintainer.hpp"
#include "param_mapping.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_user.hpp"
#include "parameter.hpp"
#include "parameter_identifier.hpp"

namespace registry
{
    namespace parameter
    {

#define REGISTRY_OFFSET (FLASH_PAGE_SIZE * 4096)
#define REGISTRY_FLASH_START (XIP_BASE + REGISTRY_OFFSET)
#define REGISTRY_BACKUP_OFFSET (REGISTRY_OFFSET + FLASH_SECTOR_SIZE)
#define REGISTRY_BACKUP_FLASH_START (XIP_BASE + REGISTRY_BACKUP_OFFSET)

#define PARAM_CONTENT_OFFSET 2

        /**
            \name Parameter storage (RAM)

            Size of all the parameter and 2 bytes CRC-16 (XMODEM)
        */

        /* @{ */
        uint8_t *const registry_start = (uint8_t *)REGISTRY_FLASH_START;

        uint8_t *const param_start = registry_start;
        uint8_t *const g_param_backlight = param_start;
        uint8_t *const g_param_display = (uint8_t *)(g_param_backlight + PARAM_CONTENT_OFFSET + sizeof(backlight::register_t));
        uint8_t *const g_param_features = (uint8_t *)(g_param_display + PARAM_CONTENT_OFFSET + sizeof(display::register_t));
        uint8_t *const g_param_keypad = (uint8_t *)(g_param_features + PARAM_CONTENT_OFFSET + sizeof(features::register_t));
        uint8_t *const g_param_maintainer = (uint8_t *)(g_param_keypad + PARAM_CONTENT_OFFSET + sizeof(keypad::register_t));
        uint8_t *const g_param_mapping = (uint8_t *)(g_param_maintainer + PARAM_CONTENT_OFFSET + sizeof(maintainer::register_t));
        uint8_t *const g_param_position = (uint8_t *)(g_param_mapping + PARAM_CONTENT_OFFSET + sizeof(mapping::register_t));
        uint8_t *const g_param_serial_number = (uint8_t *)(g_param_position + PARAM_CONTENT_OFFSET + sizeof(position::register_t));
        uint8_t *const g_param_user = (uint8_t *)(g_param_serial_number + PARAM_CONTENT_OFFSET + sizeof(serial_number::register_t));
        uint8_t *const param_crc = (uint8_t *)(g_param_user + PARAM_CONTENT_OFFSET + sizeof(user::register_t));
        uint8_t *const param_stop = (uint8_t *)(param_crc + sizeof(uint16_t));
        /* @} */

        /**
            \name Parameter backup (RAM)

            Size: l.u.
        */
        /* @{ */
        uint8_t *const backup_start = (uint8_t *)REGISTRY_BACKUP_FLASH_START;
        uint8_t *const backup_backlight = backup_start;
        uint8_t *const backup_display = (uint8_t *)(backup_backlight + PARAM_CONTENT_OFFSET + sizeof(backlight::register_t));
        uint8_t *const backup_features = (uint8_t *)(backup_display + PARAM_CONTENT_OFFSET + sizeof(display::register_t));
        uint8_t *const backup_keypad = (uint8_t *)(backup_features + PARAM_CONTENT_OFFSET + sizeof(features::register_t));
        uint8_t *const backup_maintainer = (uint8_t *)(backup_keypad + PARAM_CONTENT_OFFSET + sizeof(keypad::register_t));
        uint8_t *const backup_mapping = (uint8_t *)(backup_maintainer + PARAM_CONTENT_OFFSET + sizeof(maintainer::register_t));
        uint8_t *const backup_position = (uint8_t *)(backup_mapping + PARAM_CONTENT_OFFSET + sizeof(mapping::register_t));
        uint8_t *const backup_serial_number = (uint8_t *)(backup_position + PARAM_CONTENT_OFFSET + sizeof(position::register_t));
        uint8_t *const backup_user = (uint8_t *)(backup_serial_number + PARAM_CONTENT_OFFSET + sizeof(serial_number::register_t));
        uint8_t *const backup_crc = (uint8_t *)(backup_user + PARAM_CONTENT_OFFSET + sizeof(user::register_t));
        uint8_t *const backup_stop = (uint8_t *)(backup_crc + sizeof(uint16_t));

        uint8_t *const registry_stop = backup_stop;
        /* @} */

        static uint16_t calculate_crc(uint8_t *const _target, size_t _size);
        static uint16_t checksum_calculation(const uint8_t *_param, const size_t _size, const uint16_t _result);

        static result_t param_save(uint8_t *const _target);

        static result_t backlight_store(uint8_t *const _param);
        static result_t display_store(uint8_t *const _param);
        static result_t features_store(uint8_t *const _param);
        static result_t keypad_store(uint8_t *const _param);
        static result_t maintainer_store(uint8_t *const _param);
        static result_t mapping_store(uint8_t *const _param);
        static result_t position_store(uint8_t *const _param);
        static result_t serial_number_store(uint8_t *const _param);
        static result_t user_store(uint8_t *const _param);

        static result_t backlight_load(uint8_t *const _source);
        static result_t display_load(uint8_t *const _source);
        static result_t features_load(uint8_t *const _source);
        static result_t keypad_load(uint8_t *const _source);
        static result_t maintainer_load(uint8_t *const _source);
        static result_t mapping_load(uint8_t *const _source);
        static result_t position_load(uint8_t *const _source);
        static result_t serial_number_load(uint8_t *const _source);
        static result_t user_load(uint8_t *const _source);

#if defined(DEBUG_MEMORY_PRINTOUT)
#include <stdio.h>
        extern void debug_out_mem()
        {
            size_t size = param_crc - g_param_features + 2;
            // uint32_t size = (uint32_t)(param_crc - g_param_features);
            printf("param  mem (%8ld): ", size);
            for (int i = 0; i < size; ++i)
            {
                // printf("%02x ", i);
                printf("%02x ", g_param_features[i]);
                // printf("%02x ", (uint8_t)*(registry_start + i));
            }
            printf("\n");

            size = backup_crc - backup_features + 2;
            printf("backup mem (%8ld): ", size);
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
            backlight::g_register.initialize();
            display::g_register.initialize();
            features::g_register.initialize();
            keypad::g_register.initialize();
            maintainer::g_register.initialize();
            mapping::g_register.initialize();
            position::g_register.initialize();
            serial_number::g_register.initialize();
            user::g_register.initialize();

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
            param_keypad_load();
            param_maintainer_load();
            param_mapping_load();
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
            keypad_load(backup_keypad);
            maintainer_load(backup_maintainer);
            mapping_load(backup_maintainer);
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
            \brief Load mapping from the persistent memory

            Set proper mapping value for medium layer identity
        */
        extern result_t param_mapping_load(void)
        {
            return mapping_load(g_param_mapping);
        }

        /**
            \brief Store mapping parameter value to the persistent memory
        */
        extern result_t param_mapping_store(void)
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
        extern result_t param_keypad_load(void)
        {
            return keypad_load(g_param_keypad);
        }

        /**
            \brief Store value to the persistence memory
        */
        extern result_t param_keypad_store(void)
        {
            return param_save(registry_start);
        }

        /**
            \brief Load value from the persistence memory
        */
        extern result_t param_display_load(void)
        {
            return display_load(g_param_display);
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
            for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i)
            {
                data[i] = _target[i];
            }

            uint8_t *data_ptr = data;
            uint8_t *start = data_ptr;

            /* store parameter into the RAM array */
            backlight_store(data_ptr);
            data_ptr += sizeof(backlight::register_t) + PARAM_CONTENT_OFFSET;

            display_store(data_ptr);
            data_ptr += sizeof(display::register_t) + PARAM_CONTENT_OFFSET;

            features_store(data_ptr);
            data_ptr += sizeof(features::register_t) + PARAM_CONTENT_OFFSET;

            keypad_store(data_ptr);
            data_ptr += sizeof(keypad::register_t) + PARAM_CONTENT_OFFSET;

            maintainer_store(data_ptr);
            data_ptr += sizeof(maintainer::register_t) + PARAM_CONTENT_OFFSET;

            mapping_store(data_ptr);
            data_ptr += sizeof(mapping::register_t) + PARAM_CONTENT_OFFSET;

            position_store(data_ptr);
            data_ptr += sizeof(position::register_t) + PARAM_CONTENT_OFFSET;

            serial_number_store(data_ptr);
            data_ptr += sizeof(serial_number::register_t) + PARAM_CONTENT_OFFSET;

            user_store(data_ptr);
            data_ptr += user::SIZE + PARAM_CONTENT_OFFSET;

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
            for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i)
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
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::BACKLIGHT);
            _param[1] = sizeof(backlight::register_t);

            /* store latitude and longitude */
            for (uint8_t i = 0; i < sizeof(backlight::register_t); ++i)
            {
                _param[2 + i] = backlight::g_register.byte[i];
            }

            return SUCCESS;
        }

        static result_t display_store(uint8_t *const _param)
        {
            /* store control information */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::DISPLAY);
            _param[1] = sizeof(display::register_t);

            /* store display parameter */
            for (uint8_t i = 0; i < sizeof(display::register_t); ++i)
            {
                _param[2 + i] = display::g_register.byte[i];
            }

            return SUCCESS;
        }

        static result_t features_store(uint8_t *const _param)
        {
            /* store parameter infos */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::FEATURES);
            _param[1] = sizeof(features::register_t);

            /* store parameter value to the persistence memory */
            for (uint8_t i = 0; i < sizeof(features::register_t); ++i)
            {
                _param[2 + i] = features::g_register.byte[i];
            }

            return SUCCESS;
        }

        static result_t maintainer_store(uint8_t *const _param)
        {
            /* store parameter value */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::MAINTAINER);
            _param[1] = sizeof(maintainer::register_t);

            _param[2] = HIBYTE(maintainer::g_register.word);
            _param[3] = LOBYTE(maintainer::g_register.word);

            return SUCCESS;
        }

        static result_t mapping_store(uint8_t *const _param)
        {
            /* store parameter value */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::MAPPING);
            _param[1] = sizeof(mapping::register_t);

            for (uint8_t i = 0; i < mapping::SIZE; ++i)
            {
                _param[2 + i * sizeof(mapping::keycode_t) + 0] = mapping::g_register.value[i].modifier;
                _param[2 + i * sizeof(mapping::keycode_t) + 1] = mapping::g_register.value[i].code;
            }

            return SUCCESS;
        }

        static result_t position_store(uint8_t *const _param)
        {
            /* store control information */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::POSITION);
            _param[1] = sizeof(position::register_t);

            /* store latitude and longitude */
            for (uint8_t i = 0; i < sizeof(position::register_t); ++i)
            {
                _param[2 + i] = position::g_register.byte[i];
            }

            return SUCCESS;
        }

        static result_t serial_number_store(uint8_t *const _param)
        {
            /* deserialize parameter value */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::SERIAL_NUMBER);
            _param[1] = serial_number::SIZE;

            for (uint8_t i = 0; i < serial_number::SIZE; ++i)
            {
                _param[2 + i] = serial_number::g_register.value[i];
            }

            return SUCCESS;
        }

        static result_t keypad_store(uint8_t *const _param)
        {
            /* store control information */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::KEYPAD);
            _param[1] = sizeof(keypad::register_t);

            /* store latitude and longitude */
            for (uint8_t i = 0; i < sizeof(keypad::register_t); ++i)
            {
                _param[2 + i] = keypad::g_register.byte[i];
            }

            return SUCCESS;
        }

        static result_t user_store(uint8_t *const _param)
        {
            /* store test register */
            _param[0] = static_cast<const uint8_t>(IDENTIFIER::USER);
            _param[1] = registry::parameter::user::SIZE;

            _param[2] = registry::parameter::user::g_register.value[0];
            _param[3] = registry::parameter::user::g_register.value[1];

            return SUCCESS;
        }

        static result_t backlight_load(uint8_t *const _source)
        {
            /* check for plausibility */
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            if (identifier != IDENTIFIER::BACKLIGHT ||
                length != sizeof(backlight::register_t))
            {
                backlight::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            backlight::g_register.initialize();

            /* load latitude and longitude */
            for (uint8_t i = 0; i < sizeof(backlight::register_t); ++i)
            {
                backlight::g_register.byte[i] = _source[2 + i];
            }

            return SUCCESS;
        }

        static result_t display_load(uint8_t *const _source)
        {
            /* check for plausibility */
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            if (identifier != IDENTIFIER::DISPLAY ||
                length != sizeof(display::register_t))
            {
                display::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            display::g_register.initialize();

            /* load latitude and longitude */
            for (uint8_t i = 0; i < sizeof(display::register_t); ++i)
            {
                display::g_register.byte[i] = _source[2 + i];
            }

            return SUCCESS;
        }

        static result_t features_load(uint8_t *const _source)
        {
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            /* check for plausibility */
            if (identifier != IDENTIFIER::FEATURES ||
                length != sizeof(features::register_t))
            {
                /* set default values */
                features::g_register.initialize();
                return FAILURE;
            }

            /* load features */
            for (uint8_t i = 0; i < sizeof(features::register_t); ++i)
            {
                features::g_register.byte[i] = _source[2 + i];
            }

            return SUCCESS;
        }

        static result_t keypad_load(uint8_t *const _source)
        {
            /* check for plausibility */
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            if (identifier != IDENTIFIER::KEYPAD ||
                length != sizeof(keypad::register_t))
            {
                keypad::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            keypad::g_register.initialize();

            /* load latitude and longitude */
            for (uint8_t i = 0; i < sizeof(keypad::register_t); ++i)
            {
                keypad::g_register.byte[i] = _source[2 + i];
            }

            return SUCCESS;
        }

        static result_t maintainer_load(uint8_t *const _source)
        {
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            /* check for plausibility */
            if (identifier != IDENTIFIER::MAINTAINER ||
                length != sizeof(maintainer::register_t))
            {
                maintainer::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            maintainer::g_register.initialize();

            /* load maintainer */
            maintainer::g_register.word = SETWORD(_source[2], _source[3]);

            return SUCCESS;
        }

        static result_t mapping_load(uint8_t *const _source)
        {
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            /* check for plausibility */
            if (identifier != IDENTIFIER::MAPPING ||
                length != sizeof(mapping::register_t))
            {
                mapping::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            mapping::g_register.initialize();

            /* load parameter value */
            for (uint8_t i = 0; i < mapping::SIZE; ++i)
            {
                mapping::g_register.value[i].modifier = _source[2 + i * sizeof(mapping::keycode_t) + 0];
                mapping::g_register.value[i].code = _source[2 + i * sizeof(mapping::keycode_t) + 1];
            }

            return SUCCESS;
        }

        static result_t position_load(uint8_t *const _source)
        {
            /* check for plausibility */
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            if (identifier != IDENTIFIER::POSITION ||
                length != sizeof(position::register_t))
            {
                position::g_register.initialize();
                return FAILURE;
            }

            /* set default values */
            position::g_register.initialize();

            /* load latitude and longitude */
            for (uint8_t i = 0; i < sizeof(position::register_t); ++i)
            {
                position::g_register.byte[i] = _source[2 + i];
            }

            return SUCCESS;
        }

        static result_t serial_number_load(uint8_t *const _source)
        {
            /* check for plausibility */
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            /* load parameter value */
            for (uint8_t i = 0; i < serial_number::SIZE; ++i)
            {
                serial_number::g_register.value[i] = _source[2 + i];
            }

            serial_number::g_unique_key = SETLONG(SETWORD(serial_number::g_register.value[serial_number::SIZE - 4],
                                                          serial_number::g_register.value[serial_number::SIZE - 3]),
                                                  SETWORD(serial_number::g_register.value[serial_number::SIZE - 2],
                                                          serial_number::g_register.value[serial_number::SIZE - 1]));

            /*  check plausibility: 1) wrong identifier or length, 2) empty the persistence memory */
            if (identifier != IDENTIFIER::SERIAL_NUMBER ||
                length != serial_number::SIZE ||
                serial_number::g_unique_key == serial_number::INVALID_VALUE)
            {
                /* serial number is not valid => create new one */
                serial_number::g_register.initialize();
                return FAILURE;
            }

            return SUCCESS;
        }

        static result_t user_load(uint8_t *const _source)
        {
            const IDENTIFIER identifier = static_cast<const IDENTIFIER>(_source[0]);
            const uint8_t length = _source[1];

            /* check for plausibility */
            if (identifier != IDENTIFIER::USER ||
                length != registry::parameter::user::SIZE)
            {
                user::g_register.initialize();
                return FAILURE;
            }

            /* load test register */
            user::g_register.value[0] = _source[2];
            user::g_register.value[1] = _source[3];

            return SUCCESS;
        }

    }
}