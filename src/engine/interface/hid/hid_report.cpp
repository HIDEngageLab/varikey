/**
 * \file hid_report.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <string>

#include "board.hpp"
#include "hid_report.hpp"

namespace engine
{
    namespace hid
    {
        void set_report_t::deserialize(const const_chunk_t &_buffer)
        {
            assert(_buffer.size <= MAX_REPORT_SIZE);

            identifier = static_cast<SET_REPORT>(_buffer.space[0]);
            memcpy((void *)buffer, (void *)&_buffer.space[1], _buffer.size - 1);
        }

        void set_report_t::serialize(const chunk_t &_buffer) const
        {
            assert(_buffer.size <= MAX_REPORT_SIZE);

            _buffer.space[0] = static_cast<const uint8_t>(identifier);
            memcpy((void *)&_buffer.space[1], (void *)buffer, _buffer.size - 1);
        }

        void get_report_t::deserialize(const const_chunk_t &_buffer)
        {
            switch (identifier)
            {
            case GET_REPORT::SERIAL:
                identity.identifier = engine::payload::identity::IDENTIFIER::SERIAL;
                identity.deserialize(_buffer.space);
                break;
            case GET_REPORT::UNIQUE:
                identity.identifier = engine::payload::identity::IDENTIFIER::UNIQUE;
                identity.deserialize(_buffer.space);
                break;
            case GET_REPORT::FIRMWARE:
                identity.identifier = engine::payload::identity::IDENTIFIER::FIRMWARE;
                identity.deserialize(_buffer.space);
                break;
            case GET_REPORT::HARDWARE:
                identity.identifier = engine::payload::identity::IDENTIFIER::HARDWARE;
                identity.deserialize(_buffer.space);
                break;
            case GET_REPORT::TEMPERATURE:
                temperature.deserialize(_buffer.space);
                break;

            default:
                break;
            }
        }

        void get_report_t::serialize(const chunk_t &_buffer) const
        {
            switch (identifier)
            {
            case GET_REPORT::SERIAL:
            {
                const engine::payload::identity::content_t identity{.identifier = engine::payload::identity::IDENTIFIER::SERIAL};
                identity.serialize(_buffer.space);
                break;
            }
            case GET_REPORT::UNIQUE:
            {
                const engine::payload::identity::content_t identity{.identifier = engine::payload::identity::IDENTIFIER::UNIQUE};
                identity.serialize(_buffer.space);
                break;
            }
            case GET_REPORT::FIRMWARE:
            {
                const engine::payload::identity::content_t identity{.identifier = engine::payload::identity::IDENTIFIER::FIRMWARE};
                identity.serialize(_buffer.space);
                break;
            }
            case GET_REPORT::HARDWARE:
            {
                const engine::payload::identity::content_t identity{.identifier = engine::payload::identity::IDENTIFIER::HARDWARE};
                identity.serialize(_buffer.space);
                break;
            }
            case GET_REPORT::TEMPERATURE:
            {
                const engine::payload::temperature::content_t temperature{
                    .function = engine::payload::temperature::FUNCTION::GET,
                    .value = board.soc.get_temperature() * 1000,
                };
                temperature.serialize(_buffer.space);
            }
            default:
                break;
            }
        }
    }
}
