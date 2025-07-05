// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Registry interface implementation
// SPDX-FileType: SOURCE

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "checksum.hpp"
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
#include "random.hpp"
#include "registry.hpp"
#include "registry_interface.hpp"

namespace registry
{

    extern result_t backlight_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_backlight_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::backlight::register_t));

            uint8_t *ptr = _chunk.space;
            parameter::backlight::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::backlight::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t backlight_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        assert(_chunk.size == sizeof(parameter::backlight::register_t));

        parameter::backlight::g_register.deserialize(_chunk.space);
        if (parameter::param_backlight_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t display_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_display_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::display::register_t));

            uint8_t *ptr = _chunk.space;
            parameter::display::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::display::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t display_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        assert(_chunk.size == sizeof(parameter::display::register_t));

        parameter::display::g_register.deserialize(_chunk.space);
        if (parameter::param_display_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t features_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        assert(_chunk.space != NULL);

        if (parameter::param_features_load() == SUCCESS)
        {
            uint8_t *ptr = _chunk.space;
            parameter::features::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::features::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t features_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        parameter::features::g_register.deserialize(_chunk.space);

        if (parameter::param_features_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t keypad_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_keypad_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::keypad::register_t));

            uint8_t *ptr = _chunk.space;
            parameter::keypad::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::keypad::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t keypad_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        assert(_chunk.size == 4);

        parameter::keypad::g_register.deserialize(_chunk.space);
        if (parameter::param_keypad_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t maintainer_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_maintainer_load() == SUCCESS)
        {
            uint8_t *ptr = _chunk.space;
            parameter::maintainer::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::maintainer::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t maintainer_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        parameter::maintainer::g_register.deserialize(_chunk.space);
        if (parameter::param_maintainer_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t mapping_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_mapping_load() == SUCCESS)
        {
            uint8_t *ptr = _chunk.space;
            parameter::mapping::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::mapping::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t mapping_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        parameter::mapping::g_register.deserialize(_chunk.space);
        if (parameter::param_mapping_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t mapping_get(const uint8_t _index, chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        using namespace registry::parameter;

        if (parameter::param_mapping_load() == SUCCESS)
        {
            if (_index < mapping::SIZE)
            {

                const mapping::item_t item = {
                    .item = {
                        .index = _index,
                        .value = {
                            .modifier = mapping::g_register.value[_index].modifier,
                            .code = mapping::g_register.value[_index].code,
                        },
                    },
                };
                item.serialize(&_chunk.space);
                _chunk.size = sizeof(mapping::item_t);
                return SUCCESS;
            }
        }
        return FAILURE;
    }

    extern result_t mapping_set(const uint8_t _index, const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        using namespace registry::parameter;

        if (_index < mapping::SIZE)
        {

            mapping::item_t mapping;
            mapping.deserialize(_chunk.space);

            mapping::g_register.value[_index].modifier = mapping.item.value.modifier;
            mapping::g_register.value[_index].code = mapping.item.value.code;

            if (parameter::param_mapping_store() == SUCCESS)
            {
                return SUCCESS;
            }
        }
        return FAILURE;
    }

    extern result_t position_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_position_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::position::register_t));

            uint8_t *ptr = _chunk.space;
            parameter::position::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::position::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t position_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);
        assert(_chunk.size == 8);

        parameter::position::g_register.deserialize(_chunk.space);
        if (parameter::param_position_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t serial_number_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_serial_number_load() == SUCCESS)
        {
            uint8_t *ptr = _chunk.space;
            parameter::serial_number::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::serial_number::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t serial_number_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        parameter::serial_number::g_register.deserialize(_chunk.space);
        if (parameter::param_serial_number_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    extern result_t user_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        if (parameter::param_user_load() == SUCCESS)
        {
            uint8_t *ptr = _chunk.space;
            parameter::user::g_register.serialize(&ptr);
            _chunk.size = sizeof(parameter::user::register_t);

            return SUCCESS;
        }

        return FAILURE;
    }

    extern result_t user_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);

        parameter::user::g_register.deserialize(_chunk.space);
        if (parameter::param_user_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }
}
