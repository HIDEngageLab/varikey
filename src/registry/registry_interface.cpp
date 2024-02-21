/**
 * \file registry_interface.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief configure node components with persistent parameter

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

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
    /**
        \brief Get BACKLIGHT parameters

        BACKLIGHT combine a two float values: reference voltage and rotation wheel voltage
    */
    extern result_t backlight_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize adc */
        if (parameter::param_backlight_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::backlight::register_t)); /* node param adc chunk null */

            parameter::backlight::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::backlight::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save BACKLIGHT parameter value
    */
    extern result_t backlight_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);                                   /* state should be initialized */
        assert(_chunk.size == sizeof(parameter::backlight::register_t)); /* chunk is not null */

        /* deserialize and save backlight */
        parameter::backlight::g_register.deserialize(_chunk.space);
        if (parameter::param_backlight_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get DISPLAY parameters
    */
    extern result_t display_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize display */
        if (parameter::param_display_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::display::register_t)); /* node param display chunk null */

            parameter::display::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::display::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save DISPLAY parameter value
    */
    extern result_t display_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS);                                 /* state should be initialized */
        assert(_chunk.size == sizeof(parameter::display::register_t)); /* chunk is not null */

        /* deserialize and save display */
        parameter::display::g_register.deserialize(_chunk.space);
        if (parameter::param_display_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get features level parameter value
    */
    extern result_t features_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */
        assert(_chunk.space != NULL);  /* chunk is not null */

        /* load and serialize parameter value */
        if (parameter::param_features_load() == SUCCESS)
        {
            parameter::features::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::features::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save parameter value
    */
    extern result_t features_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* deserialize and save parameter value */
        parameter::features::g_register.deserialize(_chunk.space);

        if (parameter::param_features_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get KEYPAD parameters
    */
    extern result_t keypad_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize keypad */
        if (parameter::param_keypad_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::keypad::register_t)); /* node param key chunk null */

            parameter::keypad::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::keypad::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save KEYPAD parameter value
    */
    extern result_t keypad_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */
        assert(_chunk.size == 4);      /* chunk is not null */

        /* deserialize and save keypad */
        parameter::keypad::g_register.deserialize(_chunk.space);
        if (parameter::param_keypad_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get maintainer parameter value
    */
    extern result_t maintainer_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize parameter value */
        if (parameter::param_maintainer_load() == SUCCESS)
        {
            parameter::maintainer::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::maintainer::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save parameter value
    */
    extern result_t maintainer_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* deserialize, set and save parameter value*/
        parameter::maintainer::g_register.deserialize(_chunk.space);
        if (parameter::param_maintainer_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get serial number value
    */
    extern result_t mapping_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize serial number */
        if (parameter::param_mapping_load() == SUCCESS)
        {
            parameter::mapping::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::mapping::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief  Save serial number value
        is unsupported
    */
    extern result_t mapping_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* deserialize and save */
        parameter::mapping::g_register.deserialize(_chunk.space);
        if (parameter::param_mapping_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get node position

        Position combine a two long values: latitude and longitude
    */
    extern result_t position_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize position */
        if (parameter::param_position_load() == SUCCESS)
        {
            assert(_chunk.size >= sizeof(parameter::position::register_t)); /* node param position chunk null */

            parameter::position::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::position::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Save parameter value
    */
    extern result_t position_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */
        assert(_chunk.size == 8);      /* chunk is not null */

        /* deserialize and save position */
        parameter::position::g_register.deserialize(_chunk.space);
        if (parameter::param_position_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get serial number value
    */
    extern result_t serial_number_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* load and serialize serial number */
        if (parameter::param_serial_number_load() == SUCCESS)
        {
            parameter::serial_number::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::serial_number::register_t);

            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief  Save serial number value
        is unsupported
    */
    extern result_t serial_number_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* deserialize and save */
        parameter::serial_number::g_register.deserialize(_chunk.space);
        if (parameter::param_serial_number_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }

    /**
        \brief Get user register value
    */
    extern result_t user_get(chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* serialize parameter value */
        if (parameter::param_user_load() == SUCCESS)
        {
            parameter::user::g_register.serialize(_chunk.space);
            _chunk.size = sizeof(parameter::user::register_t);

            return SUCCESS;
        }

        return FAILURE;
    }

    /**
        \brief Save parameter value
    */
    extern result_t user_set(const const_chunk_t &_chunk)
    {
        assert(is_ready() == SUCCESS); /* state should be initialized */

        /* deserialize parameter value */
        parameter::user::g_register.deserialize(_chunk.space);
        if (parameter::param_user_store() == SUCCESS)
        {
            return SUCCESS;
        }
        return FAILURE;
    }
}
