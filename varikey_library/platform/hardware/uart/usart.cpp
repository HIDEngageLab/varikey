// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: USART communication implementation
// SPDX-FileType: SOURCE

#include <hardware/irq.h>
#include <hardware/sync.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "bytering.hpp"
#include "usart.hpp"

#define INT_GUARD_OPEN() uint32_t ints = save_and_disable_interrupts();
#define INT_GUARD_CLOSE() restore_interrupts(ints);

usart_rx_tx_handler_t g_usart_rx_tx_handler = 0;

namespace platform::hardware
{
    uint8_t usart_rx_space[UartDevice::USART_SPACE_SIZE];
    buffer_t usart_rx_buffer;
    uint8_t usart_tx_space[UartDevice::USART_SPACE_SIZE];
    buffer_t usart_tx_buffer;

    static void send_byte_to_tx()
    {
        uint8_t byte;
        if (bytering_peek(&usart_tx_buffer, 0, &byte))
        {
            if (uart_is_writable(uart0))
            {
                bytering_read(&usart_tx_buffer, &byte);
                uart_putc(uart0, byte);
            }
        }
        else
        {
            uart_set_irq_enables(uart0, true, false);
        }
    }

    static void on_uart_irq()
    {

        while (uart_is_readable(uart0))
        {
            const uint8_t byte = uart_getc(uart0);
            bytering_write(&usart_rx_buffer, byte);
        }
        send_byte_to_tx();
    }

    void UartDevice::initialize()
    {
        bytering_init(&usart_rx_buffer, usart_rx_space, USART_SPACE_SIZE);
        bytering_init(&usart_tx_buffer, usart_tx_space, USART_SPACE_SIZE);

        uart_deinit(uart0);
        uart_init(uart0, BAUD_RATE);

        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

        int __unused actual = uart_set_baudrate(uart0, BAUD_RATE);
        uart_set_hw_flow(uart0, false, false);
        uart_set_format(uart0, DATA_BITS, STOP_BITS, PARITY);
        uart_set_fifo_enabled(uart0, false);

        int UART_IRQ = uart0 == uart0 ? UART0_IRQ : UART1_IRQ;

        irq_set_exclusive_handler(UART_IRQ, on_uart_irq);
        irq_set_enabled(UART_IRQ, true);

        uart_set_irq_enables(uart0, true, false);
    }

    void UartDevice::shutdown()
    {
        uart_set_irq_enables(uart0, false, false);
        uart_deinit(uart0);
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_NULL);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_NULL);
    }

    void UartDevice::perform()
    {
        INT_GUARD_OPEN();
        if (g_usart_rx_tx_handler != NULL)
        {

            g_usart_rx_tx_handler(&usart_rx_buffer, &usart_tx_buffer);
        }
        else
        {
            echo();
        }

        if (usart_tx_buffer.number_of_free_items < USART_SPACE_SIZE)
        {

            uart_set_irq_enables(uart0, true, true);
            send_byte_to_tx();
        }
        else
        {
            uart_set_irq_enables(uart0, true, false);
        }
        INT_GUARD_CLOSE();
    }

    void UartDevice::usart_last_whisper(uint8_t const _byte)
    {
        uart_putc(uart0, _byte);
    }

    int UartDevice::uart_putchar(char c, FILE *stream)
    {
        (void)stream;
        INT_GUARD_OPEN();
        bytering_write(&usart_tx_buffer, c);
        INT_GUARD_CLOSE();
        return 0;
    }

    void UartDevice::echo()
    {

        bytering_copy(&usart_rx_buffer, &usart_tx_buffer);
    }
}
