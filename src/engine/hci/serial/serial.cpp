/**
 * \file serial.cpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Entry point for serial engine, data exchange over UART interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "serial.hpp"
#include "commander.hpp"
#include "serial_frame.hpp"
#include "usart.hpp"

/**
    \brief  Initialize serial engine
*/
extern void serial_init(void)
{
    /* set external dependency between core USART module and the serial engine */
    g_usart_rx_tx_handler = serial_frame_usart_data_handler;

    /* initialize serial engine */
    serial_frame_init();
    /* register interpreter with address by serial frame handler */
    serial_frame_register_handler(SERIAL_COMMANDER_INTERPRETER_ADDRESS, hci_commander_interpreter);
}

/**
    \brief Start serial engine
*/
extern void serial_start(void)
{
#if defined(ENABLE_MONITORING)
    serial_monitor_start();
#endif
}
