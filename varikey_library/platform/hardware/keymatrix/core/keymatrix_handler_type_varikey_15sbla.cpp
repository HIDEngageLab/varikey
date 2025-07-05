// SPDX-FileCopyrightText: 2024 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix handler type varikey 15sbla functionality
// SPDX-FileType: SOURCE

#include "keymatrix_handler_type_varikey_15sbla.hpp"
#include "keymatrix_core_event.hpp"
#include "keymatrix_core_handler.hpp"
#include "keypad.hpp"

namespace platform::hardware
{
    static engine::keypad::STATE get_key_state(const platform::hardware::pico::event::STATE _state)
    {
        switch (_state)
        {
        case platform::hardware::pico::event::STATE::PRESS:
            return engine::keypad::STATE::PRESS;
        case platform::hardware::pico::event::STATE::RELEASE:
            return engine::keypad::STATE::RELEASE;
        default:
            break;
        }

        return engine::keypad::STATE::UNDEFINED;
    }

    void KeymatrixHandlerVarikey15SBLA::event_handler(const platform::hardware::pico::event_t _event)
    {
        switch (_event.identifier)
        {
        case platform::hardware::pico::event::IDENTIFIER::UNDEFINED:
            break;
        case platform::hardware::pico::event::IDENTIFIER::R1_C1:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_01, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R1_C2:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_02, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R1_C3:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_03, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R1_C4:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_04, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R1_C5:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_05, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R2_C1:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_06, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R2_C2:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_07, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R2_C3:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_08, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R2_C4:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_09, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R2_C5:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_10, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R3_C1:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_11, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R3_C2:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_12, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R3_C3:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_13, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R3_C4:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_14, get_key_state(_event.state));
            break;
        case platform::hardware::pico::event::IDENTIFIER::R3_C5:
            engine::keypad::switch_key(engine::keypad::KEY_ID::KEY_15, get_key_state(_event.state));
            break;
        default:
            break;
        }
    }
}
