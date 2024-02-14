/**
 * \file commander.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Command interpreter on the host interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __SERIAL_COMMANDER_HPP__
#define __SERIAL_COMMANDER_HPP__

#include <stdint.h>

#include "chunk.h"
#include "cmd_protocol_msg.hpp"

namespace engine
{
    namespace hci
    {
        static const uint8_t INTERPRETER_ADDRESS = 0x20;

        /** \brief Message primitives */
        enum class SUFFIX : uint8_t
        {
            REQ = 0x00,
            CFM = 0x01,
            IND = 0x02,
            RES = 0x03,
        };

        namespace hc
        {
            /*
                python lines to print proper command codes

                CMD_REQ = 0
                CMD_CFM = 1
                CMD_IND = 2
                CMD_RES = 3
                CMD_OFFSET = 2

                for i in range(0, 20):
                    str = '0x%02X ' % i
                    str += "REQ:0x%02X " % ((i << CMD_OFFSET) + CMD_REQ)
                    str += "CFM:0x%02X " % ((i << CMD_OFFSET) + CMD_CFM)
                    str += "IND:0x%02X " % ((i << CMD_OFFSET) + CMD_IND)
                    str += "RES:0x%02X " % ((i << CMD_OFFSET) + CMD_RES)
                    print(str)

                result:

                0x00 REQ:0x00 CFM:0x01 IND:0x02 RES:0x03
                0x01 REQ:0x04 CFM:0x05 IND:0x06 RES:0x07
                0x02 REQ:0x08 CFM:0x09 IND:0x0A RES:0x0B
                0x03 REQ:0x0C CFM:0x0D IND:0x0E RES:0x0F
                0x04 REQ:0x10 CFM:0x11 IND:0x12 RES:0x13
                0x05 REQ:0x14 CFM:0x15 IND:0x16 RES:0x17
                0x06 REQ:0x18 CFM:0x19 IND:0x1A RES:0x1B
                0x07 REQ:0x1C CFM:0x1D IND:0x1E RES:0x1F
                0x08 REQ:0x20 CFM:0x21 IND:0x22 RES:0x23
                0x09 REQ:0x24 CFM:0x25 IND:0x26 RES:0x27
                0x0A REQ:0x28 CFM:0x29 IND:0x2A RES:0x2B
                0x0B REQ:0x2C CFM:0x2D IND:0x2E RES:0x2F
                0x0C REQ:0x30 CFM:0x31 IND:0x32 RES:0x33
                0x0D REQ:0x34 CFM:0x35 IND:0x36 RES:0x37
                0x0E REQ:0x38 CFM:0x39 IND:0x3A RES:0x3B
                0x0F REQ:0x3C CFM:0x3D IND:0x3E RES:0x3F
                0x10 REQ:0x40 CFM:0x41 IND:0x42 RES:0x43
                0x11 REQ:0x44 CFM:0x45 IND:0x46 RES:0x47
                0x12 REQ:0x48 CFM:0x49 IND:0x4A RES:0x4B
                0x13 REQ:0x4C CFM:0x4D IND:0x4E RES:0x4F
            */

            static const uint8_t BACKLIGHT = 0x0e;
            static const uint8_t DISPLAY = 0x08;
            static const uint8_t GADGET = 0x02;
            static const uint8_t GPIO = 0x11;
            static const uint8_t HASH = 0x07;
            static const uint8_t IDENTITY = 0x05;
            static const uint8_t KEYPAD = 0x0c;
            static const uint8_t PARAMETER = 0x06;
            static const uint8_t PROTOCOL = 0x00;
            static const uint8_t RESET = 0x01;
            static const uint8_t TEMPERATURE = 0x0d;

            static const uint8_t OFFSET = 2;

            static const uint8_t BACKLIGHT_CFM_VALUE = ((BACKLIGHT << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t BACKLIGHT_REQ_VALUE = ((BACKLIGHT << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t DISPLAY_CFM_VALUE = ((DISPLAY << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t DISPLAY_REQ_VALUE = ((DISPLAY << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t GADGET_CFM_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t GADGET_IND_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t GADGET_REQ_VALUE = ((GADGET << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t GPIO_CFM_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t GPIO_IND_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t GPIO_REQ_VALUE = ((GPIO << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t HASH_CFM_VALUE = ((HASH << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t HASH_REQ_VALUE = ((HASH << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t IDENTITY_CFM_VALUE = ((IDENTITY << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t IDENTITY_REQ_VALUE = ((IDENTITY << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t KEYPAD_CFM_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t KEYPAD_IND_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t KEYPAD_REQ_VALUE = ((KEYPAD << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t PARAM_CFM_VALUE = ((PARAMETER << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t PARAM_REQ_VALUE = ((PARAMETER << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t PROTOCOL_IND_VALUE = ((PROTOCOL << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t RESET_IND_VALUE = ((RESET << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t RESET_REQ_VALUE = ((RESET << OFFSET) + (int)SUFFIX::REQ);
            static const uint8_t TEMPERATURE_CFM_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::CFM);
            static const uint8_t TEMPERATURE_IND_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::IND);
            static const uint8_t TEMPERATURE_REQ_VALUE = ((TEMPERATURE << OFFSET) + (int)SUFFIX::REQ);
        }

        /**
         * \brief HCI interface commands
         *
         * BACKLIGHT        control backlight engine
         * DISPLAY          control display
         * GADGET           check module status
         * GPIO             target control
         * HASH             calculate hash value for a data chunk
         * IDENTITY         check module identifier
         * KEYPAD           event trigger
         * PARAMETER        handle parameter request
         * RESET            module restart
         * TEMPERATURE      check temperature
         */
        enum class COMMAND : uint8_t
        {
            BACKLIGHT_CFM = hc::BACKLIGHT_CFM_VALUE,
            BACKLIGHT_REQ = hc::BACKLIGHT_REQ_VALUE,
            DISPLAY_CFM = hc::DISPLAY_CFM_VALUE,
            DISPLAY_REQ = hc::DISPLAY_REQ_VALUE,
            GADGET_CFM = hc::GADGET_CFM_VALUE,
            GADGET_IND = hc::GADGET_IND_VALUE,
            GADGET_REQ = hc::GADGET_REQ_VALUE,
            GPIO_CFM = hc::GPIO_CFM_VALUE,
            GPIO_IND = hc::GPIO_IND_VALUE,
            GPIO_REQ = hc::GPIO_REQ_VALUE,
            HASH_CFM = hc::HASH_CFM_VALUE,
            HASH_REQ = hc::HASH_REQ_VALUE,
            IDENTITY_CFM = hc::IDENTITY_CFM_VALUE,
            IDENTITY_REQ = hc::IDENTITY_REQ_VALUE,
            KEYPAD_CFM = hc::KEYPAD_CFM_VALUE,
            KEYPAD_IND = hc::KEYPAD_IND_VALUE,
            KEYPAD_REQ = hc::KEYPAD_REQ_VALUE,
            PARAM_CFM = hc::PARAM_CFM_VALUE,
            PARAM_REQ = hc::PARAM_REQ_VALUE,
            PROTOCOL_IND = hc::PROTOCOL_IND_VALUE,
            RESET_IND = hc::RESET_IND_VALUE,
            RESET_REQ = hc::RESET_REQ_VALUE,
            TEMPERATURE_CFM = hc::TEMPERATURE_CFM_VALUE,
            TEMPERATURE_IND = hc::TEMPERATURE_IND_VALUE,
            TEMPERATURE_REQ = hc::TEMPERATURE_REQ_VALUE,
        };
        extern cmd::protocol::RESULT interpreter(chunk_t const *const _chunk);
    }
}

#endif /* __SERIAL_COMMANDER_HPP__ */
