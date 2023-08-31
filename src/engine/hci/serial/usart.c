/**
 * \file usart.c
 * \author Koch, Roman (koch.roman@googlemail.com)
 * \brief
 * \version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
/**
    \brief USART controller

    \internal
    \author Roman Koch, koch.roman@googlemail.com
*/

#include <hardware/irq.h>
#include <hardware/uart.h>
#include <pico/stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "bytering.h"
#include "guard_macros.h"
#include "usart.h"

/**
     \name USART defines
 */
/* @{ */
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

/* We are using pins 0 and 1, but see the GPIO function select table in the
datasheet for information on which other pins can be used. */
#define UART_TX_PIN 0
#define UART_RX_PIN 1
/* @} */

/**
    \name Small RX buffer

    Attention: Buffer size should be a power of 2 value (l.u. byte ring implementation)
*/
/* @{ */
#define USART_SPACE_SIZE (1 << 8)

    static uint8_t usart_rx_space[USART_SPACE_SIZE];
static buffer_t usart_rx_buffer;
static uint8_t usart_tx_space[USART_SPACE_SIZE];
static buffer_t usart_tx_buffer;
/* @} */

/** \brief Global USART RX/TX handler */
usart_rx_tx_handler_t g_usart_rx_tx_handler = 0;

static int uart_putchar(char c, FILE *stream);
static void on_uart_irq();
static void send_byte_to_tx(void);

/**
    \brief Initialize interrupt controlled UART

    9600, 8bit, no parity, 2 stops
*/
extern void usart_init()
{

    bytering_init(&usart_rx_buffer, usart_rx_space, USART_SPACE_SIZE);
    bytering_init(&usart_tx_buffer, usart_tx_space, USART_SPACE_SIZE);

    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);

    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    irq_set_exclusive_handler(UART_IRQ, on_uart_irq);
    irq_set_enabled(UART_IRQ, true);
}

/**
    \brief Enable USART interrupts
*/
extern void usart_start(void)
{
    /* enable RX-IRQ */
    uart_set_irq_enables(UART_ID, true, false);
}

extern void usart_stop(void)
{
}

extern void usart_shutdown(void)
{
    uart_set_irq_enables(UART_ID, false, false);
    uart_deinit(UART_ID);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_NULL);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_NULL);
}

/**
    \brief Perform TTX/RX data exchange
*/
extern void usart_perform(void)
{
    INT_GUARD_OPEN();

    assert(g_usart_rx_tx_handler != NULL); /* data handler needs to be set */
    g_usart_rx_tx_handler(&usart_rx_buffer, &usart_tx_buffer);

    if (usart_tx_buffer.number_of_free_items < USART_SPACE_SIZE)
    {
        /* enable TX-IRQ */
        uart_set_irq_enables(UART_ID, true, true);
        send_byte_to_tx();
    }
    else
    {
        uart_set_irq_enables(UART_ID, true, false);
    }

    INT_GUARD_CLOSE();
}

/**
    \brief Print a byte

    This function should be used in emergency case only.
    All the timings can be destroyed trough this call.
*/
extern void usart_last_whisper(uint8_t const _byte)
{
    uart_putc(UART_ID, _byte);
}

/**
    \brief IRQ handler
*/
static void on_uart_irq()
{
    // uart_puts(UART_ID, "\nuart perform");

    /* todo: handle error flags */
    while (uart_is_readable(UART_ID))
    {
        uint8_t byte = uart_getc(UART_ID);
        bytering_write(&usart_rx_buffer, byte);
    }
    send_byte_to_tx();
}

static void send_byte_to_tx()
{
    uint8_t byte;
    if (bytering_peek(&usart_tx_buffer, 0, &byte))
    {
        if (uart_is_writable(UART_ID))
        {
            bytering_read(&usart_tx_buffer, &byte);
            uart_putc(UART_ID, byte);
        }
    }
    else
    {
        uart_set_irq_enables(UART_ID, true, false);
    }
}

/**
    \brief Definition of the output function for printf
*/
static int uart_putchar(char c, FILE *stream)
{
    (void)stream;
    INT_GUARD_OPEN();
    bytering_write(&usart_tx_buffer, c);
    INT_GUARD_CLOSE();
    return 0;
}
