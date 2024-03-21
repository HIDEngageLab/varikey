/**
 * \file payload_parameter.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __ENGINE_PAYLOAD_PARAMETER_HPP__
#define __ENGINE_PAYLOAD_PARAMETER_HPP__

#include <cstdint>
#include <cstdlib>

#include "chunk.h"
#include "engine_defines.hpp"
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
#include "payload_identifier.hpp"
#include "registry_defines.hpp"
#include "registry_interface.hpp"

namespace engine
{
    namespace payload
    {
        namespace parameter
        {
            using IDENTIFIER = registry::parameter::IDENTIFIER;

            /** \brief Parameter length type */
            enum class TYPELEN : uint8_t
            {
                BYTE = 0x01,
                WORD = 0x02,
                LONG = 0x04,
                BUFF = 0x80,
            };

            /** \brief parameter request function type */
            enum class FUNCTION : uint8_t
            {
                GET = common::function::GET,
                SET = common::function::SET,

                UNDEFINED = common::function::UNDEFINED,
            };

            struct content_t
            {
                IDENTIFIER identifier;
                FUNCTION function;
                union
                {
                    registry::parameter::backlight::register_t backlight;
                    registry::parameter::display::register_t display;
                    registry::parameter::features::register_t features;
                    registry::parameter::keypad::register_t keypad;
                    registry::parameter::maintainer::register_t maintainer;
                    registry::parameter::mapping::item_t mapping;
                    registry::parameter::position::register_t position;
                    registry::parameter::serial_number::register_t serial_number;
                    registry::parameter::user::register_t user;
                } parameter;

                const size_t size() const;

                void deserialize(uint8_t const *const);
                void serialize(uint8_t **) const;
            };

            extern registry::result_t set_parameter(const engine::payload::parameter::content_t &);
            extern registry::result_t get_parameter(engine::payload::parameter::content_t &);
        }
    }
}

#endif // __ENGINE_PAYLOAD_PARAMETER_HPP__
