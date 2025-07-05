// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Keymatrix core keymatrix core functionality
// SPDX-FileType: SOURCE

#include "keymatrix_core.hpp"
#include "keymatrix_queue.hpp"

namespace platform::hardware
{
    void protocol_core_init(int const _address)
    {
    }

    bool protocol_core_has_event()
    {
        return keymatrix::has_event();
    }

    void protocol_core_get_event(uint8_t *const _state, uint8_t *const _identifier)
    {
        keymatrix::KeyEvent event;
        if (keymatrix::pop_event(event))
        {
            if (event.type == keymatrix::KeyEvent::PRESS)
            {
                // printf("Key Pressed: Row %d, Col %d\n", event.row, event.col);
                *_state = 1;
            }
            else if (event.type == keymatrix::KeyEvent::RELEASE)
            {
                // printf("Key Released: Row %d, Col %d\n", event.row, event.col);
                *_state = 0;
            }
            else
            {
                *_state = 0xff; // Unbekannter Zustand
            }
            if (event.row > 0 && event.row <= 3 && event.col > 0 && event.col <= 5)
            {
                *_identifier = static_cast<uint8_t>((event.row - 1) * 5 + event.col);
            }
            else
            {
                *_identifier = 0; // Ungültiges Ereignis
            }
        }
    }
}