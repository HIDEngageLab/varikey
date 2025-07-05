// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: USART communication interface
// SPDX-FileType: SOURCE

#pragma once

#include <cstdio>
#include <hardware/uart.h>

#include "bytering.hpp"
#include "component_interface.hpp"

namespace platform::hardware
{
    struct UartDevice : public pulp::ComponentInterface
    {
        static const unsigned int USART_SPACE_SIZE = (1 << 8);

        static const int BAUD_RATE = 115200;
        static const int DATA_BITS = 8;
        static const int STOP_BITS = 1;
        static const uart_parity_t PARITY = UART_PARITY_NONE;

        static const int UART_TX_PIN = 0;
        static const int UART_RX_PIN = 1;

        virtual void initialize();
        virtual void shutdown();

        void usart_last_whisper(uint8_t const _byte);

        void perform();

    protected:
        int uart_putchar(char c, FILE *stream);

    private:
        void echo();
    };
}

typedef void (*usart_rx_tx_handler_t)(buffer_t *const _rx, buffer_t *const _tx);

extern usart_rx_tx_handler_t g_usart_rx_tx_handler;
