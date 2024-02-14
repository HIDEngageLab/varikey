/**
 * \file usart.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief USART controller

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PLATFORM_HARDWARE_USART_HPP__
#define __PLATFORM_HARDWARE_USART_HPP__

#include <cstdio>
#include <hardware/uart.h>

#include "bytering.hpp"
#include "component_interface.hpp"

namespace platform
{
    namespace hardware
    {
        struct UartDevice : public pulp::ComponentInterface
        {
            /* Attention: Buffer size should be a power of 2 value (l.u. byte ring implementation) */
            static const unsigned int USART_SPACE_SIZE = (1 << 8);

            static const int BAUD_RATE = 115200;
            static const int DATA_BITS = 8;
            static const int STOP_BITS = 1;
            static const uart_parity_t PARITY = UART_PARITY_NONE;

            /* We are using pins 0 and 1, but see the GPIO function select table in the
            data sheet for information on which other pins can be used. */
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
}

/** \brief Type for RX/TX handler */
typedef void (*usart_rx_tx_handler_t)(buffer_t *const _rx, buffer_t *const _tx);

/** \brief Global USART TR/TX handler */
extern usart_rx_tx_handler_t g_usart_rx_tx_handler;

#endif /* __PLATFORM_HARDWARE_USART_HPP__ */
