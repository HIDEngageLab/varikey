// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: serial frame module
// SPDX-FileType: SOURCE

#pragma once

#include "bytering.hpp"
#include "cmd_protocol_msg.hpp"

namespace engine::serial::frame
{
    typedef hci::cmd::protocol::RESULT (*handler_t)(chunk_t const *_chunk);

    extern void init(void);
    extern void usart_data_handler(buffer_t *const _rx_buffer, buffer_t *const _tx_buffer);
    extern void register_handler(uint8_t const _address, handler_t _handler);
    extern uint8_t send(uint8_t const _address, chunk_t const *const _chunk);
    extern void perform(void);
}
