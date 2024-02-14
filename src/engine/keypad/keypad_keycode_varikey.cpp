/**
 * \file keypad_keycode_varikey.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include <cstdint>

#include "keypad_keycode_varikey.hpp"

namespace engine
{
    namespace keypad
    {
        const code_table_t KeypadVarikey::number_value = {
            {key_code_t::SINGLE, 0, {HID_KEY_0}},
            {key_code_t::SINGLE, 0, {HID_KEY_1}},
            {key_code_t::SINGLE, 0, {HID_KEY_2}},
            {key_code_t::SINGLE, 0, {HID_KEY_3}},
            {key_code_t::SINGLE, 0, {HID_KEY_4}},
            {key_code_t::SINGLE, 0, {HID_KEY_5}},
            {key_code_t::SINGLE, 0, {HID_KEY_6}},
            {key_code_t::SINGLE, 0, {HID_KEY_7}},
            {key_code_t::SINGLE, 0, {HID_KEY_8}},
            {key_code_t::SINGLE, 0, {HID_KEY_9}},
            {key_code_t::ROTATION, 0, {HID_KEY_0, HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_PERIOD}},
            {key_code_t::ROTATION, 10, {HID_KEY_PERIOD, HID_KEY_9, HID_KEY_8, HID_KEY_7, HID_KEY_6, HID_KEY_5, HID_KEY_4, HID_KEY_3, HID_KEY_2, HID_KEY_1, HID_KEY_0}},
            {key_code_t::SINGLE, 0, {HID_KEY_BACKSPACE}},
        };

        /*
            cell phone like keypad
            1        2           3
            <-       abc         def
            4        5           6
            ghi      jkl         mno
            7        8           9
            pqrs     tuv         wxyz
                    0
                    _ CAPS_LOCK

            switch: backspace
            up/dn: sequence

            up/dn: zahlen->klein->groß
            switch: enter
         */
        const code_table_t KeypadVarikey::telephon_value = {
            {key_code_t::ROTATION, 0, {HID_KEY_1, HID_KEY_COMMA, HID_KEY_PERIOD}},
            {key_code_t::ROTATION, 0, {HID_KEY_2, HID_KEY_A, HID_KEY_B, HID_KEY_C}},
            {key_code_t::ROTATION, 0, {HID_KEY_3, HID_KEY_D, HID_KEY_E, HID_KEY_F}},
            {key_code_t::ROTATION, 0, {HID_KEY_4, HID_KEY_G, HID_KEY_H, HID_KEY_I}},
            {key_code_t::ROTATION, 0, {HID_KEY_5, HID_KEY_J, HID_KEY_K, HID_KEY_L}},
            {key_code_t::ROTATION, 0, {HID_KEY_6, HID_KEY_M, HID_KEY_N, HID_KEY_O}},
            {key_code_t::ROTATION, 0, {HID_KEY_7, HID_KEY_P, HID_KEY_Q, HID_KEY_R, HID_KEY_S}},
            {key_code_t::ROTATION, 0, {HID_KEY_8, HID_KEY_T, HID_KEY_U, HID_KEY_V}},
            {key_code_t::ROTATION, 0, {HID_KEY_9, HID_KEY_W, HID_KEY_X, HID_KEY_Y, HID_KEY_Z}},
            {key_code_t::ROTATION, 0, {HID_KEY_0, HID_KEY_SPACE, HID_KEY_CAPS_LOCK}},
            {key_code_t::ROTATION, 0, {HID_KEY_0, HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_A, HID_KEY_B, HID_KEY_C, HID_KEY_D, HID_KEY_E, HID_KEY_F, HID_KEY_G, HID_KEY_H, HID_KEY_I, HID_KEY_J, HID_KEY_K, HID_KEY_L, HID_KEY_M, HID_KEY_N, HID_KEY_O, HID_KEY_P, HID_KEY_Q, HID_KEY_R, HID_KEY_S, HID_KEY_T, HID_KEY_U, HID_KEY_V, HID_KEY_W, HID_KEY_X, HID_KEY_Y, HID_KEY_Z}},
            {key_code_t::ROTATION, 35, {HID_KEY_Z, HID_KEY_Y, HID_KEY_X, HID_KEY_W, HID_KEY_V, HID_KEY_U, HID_KEY_T, HID_KEY_S, HID_KEY_R, HID_KEY_Q, HID_KEY_P, HID_KEY_O, HID_KEY_N, HID_KEY_M, HID_KEY_L, HID_KEY_K, HID_KEY_J, HID_KEY_I, HID_KEY_H, HID_KEY_G, HID_KEY_F, HID_KEY_E, HID_KEY_D, HID_KEY_C, HID_KEY_B, HID_KEY_A, HID_KEY_9, HID_KEY_8, HID_KEY_7, HID_KEY_6, HID_KEY_5, HID_KEY_4, HID_KEY_3, HID_KEY_2, HID_KEY_1, HID_KEY_0}},
            {key_code_t::ROTATION, 0, {HID_KEY_BACKSPACE}},
        };

        const code_table_t KeypadVarikey::functional_value = {
            {key_code_t::SINGLE, 0, {HID_KEY_F1}},
            {key_code_t::SINGLE, 0, {HID_KEY_F2}},
            {key_code_t::SINGLE, 0, {HID_KEY_F3}},
            {key_code_t::SINGLE, 0, {HID_KEY_F4}},
            {key_code_t::SINGLE, 0, {HID_KEY_F5}},
            {key_code_t::SINGLE, 0, {HID_KEY_F6}},
            {key_code_t::SINGLE, 0, {HID_KEY_F7}},
            {key_code_t::SINGLE, 0, {HID_KEY_F8}},
            {key_code_t::SINGLE, 0, {HID_KEY_F9}},
            {key_code_t::SINGLE, 0, {HID_KEY_F10}},
            {key_code_t::ROTATION, 0, {HID_KEY_F1, HID_KEY_F2, HID_KEY_F3, HID_KEY_F4, HID_KEY_F5, HID_KEY_F6, HID_KEY_F7, HID_KEY_F8, HID_KEY_F9, HID_KEY_F10}},
            {key_code_t::ROTATION, 10, {HID_KEY_F10, HID_KEY_F9, HID_KEY_F8, HID_KEY_F7, HID_KEY_F6, HID_KEY_F5, HID_KEY_F4, HID_KEY_F3, HID_KEY_F2, HID_KEY_F1}},
            {key_code_t::SINGLE, 0, {HID_KEY_ESCAPE}},
        };

        const code_table_t KeypadVarikey::multimedia_value = {
            {key_code_t::SINGLE, 0, {HID_KEY_ESCAPE}},
            {key_code_t::SINGLE, 0, {HID_KEY_HELP}},
            {key_code_t::SINGLE, 0, {HID_KEY_CUT}},
            {key_code_t::SINGLE, 0, {HID_KEY_COPY}},
            {key_code_t::SINGLE, 0, {HID_KEY_PASTE}},
            {key_code_t::SINGLE, 0, {HID_KEY_PAUSE}},
            {key_code_t::SINGLE, 0, {HID_KEY_STOP}},
            {key_code_t::SINGLE, 0, {HID_KEY_CLEAR}},
            {key_code_t::SINGLE, 0, {HID_KEY_CANCEL}},
            {key_code_t::SINGLE, 0, {HID_KEY_FIND}},
            {key_code_t::SINGLE, 0, {HID_KEY_VOLUME_UP}},
            {key_code_t::SINGLE, 0, {HID_KEY_VOLUME_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_MUTE}},
        };

        const code_table_t KeypadVarikey::navigation_value = {
            {key_code_t::SINGLE, 0, {HID_KEY_ESCAPE}},
            {key_code_t::SINGLE, 0, {HID_KEY_HOME}},
            {key_code_t::SINGLE, 0, {HID_KEY_END}},
            {key_code_t::SINGLE, 0, {HID_KEY_INSERT}},
            {key_code_t::SINGLE, 0, {HID_KEY_DELETE}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_UP}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_LEFT}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_RIGHT}},
            {key_code_t::SINGLE, 0, {HID_KEY_SELECT}},
            {key_code_t::SINGLE, 0, {HID_KEY_PAGE_UP}},
            {key_code_t::SINGLE, 0, {HID_KEY_PAGE_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_ENTER}},
            {key_code_t::SINGLE, 0, {HID_KEY_PAGE_UP}},
            {key_code_t::SINGLE, 0, {HID_KEY_PAGE_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_ENTER}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_LEFT}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_RIGHT}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_UP}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_DOWN}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_LEFT}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_RIGHT}},
            {key_code_t::SINGLE, 0, {HID_KEY_ARROW_UP}},
        };

        const code_table_t KeypadVarikey::custom_value = {
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},

            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},

            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},

            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
            {key_code_t::SINGLE, 0, {0xff}},
        };
    }
}
