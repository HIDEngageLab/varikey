/**
 * \file keymatrix_adp5585_handler_gossenmetrawatt.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "keymatrix_handler_type_gmc.hpp"
#include "keymatrix_handler_adp5585.hpp"
#include "keypad.hpp"

namespace platform
{
    namespace hardware
    {
        static engine::keypad::STATE get_key_state(const platform::hardware::adp5585::event::STATE _state)
        {
            switch (_state)
            {
            case platform::hardware::adp5585::event::STATE::PRESS:
                return engine::keypad::STATE::PRESS;
            case platform::hardware::adp5585::event::STATE::RELEASE:
                return engine::keypad::STATE::RELEASE;
            default:
                break;
            }

            return engine::keypad::STATE::UNDEFINED;
        }

        void KeymatrixHandlerGmc::event_handler(const platform::hardware::adp5585::event_t _event)
        {
            switch (_event.identifier)
            {
            case platform::hardware::adp5585::event::IDENTIFIER::UNDEFINED:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_C0:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_01, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_C1:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_06, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_C0:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_02, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_C1:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_07, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_C0:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_03, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_C1:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_08, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_C0:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_04, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_C1:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_09, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_C0:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_05, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_C1:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_10, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_C0:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_C1:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_C2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_C3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_C4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_GND:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_01, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_GND:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_02, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_GND:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_03, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_GND:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_04, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_GND:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_05, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_GND:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R0_GPI_1:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R1_GPI_2:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R2_GPI_3:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R3_GPI_4:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R4_GPI_5:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::R5_GPI_6:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::C0_GPI_7:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::C1_GPI_8:
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::C2_GPI_9:
                engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_72, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::C3_GPI_10:
                push_wheel_turn(TRIGGER::UP, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::C4_GPI_11:
                push_wheel_turn(TRIGGER::DN, get_key_state(_event.state));
                break;
            case platform::hardware::adp5585::event::IDENTIFIER::LOGIC:
                break;
            default:
                break;
            }
        }
    }
}
