/**
 * \file serial.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */
/**
    \brief Entry point serial engine, data exchange over UART interface

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#ifndef __SERIAL_HPP__
#define __SERIAL_HPP__

extern void serial_init(void);
extern void serial_perform(void);

#endif /* __SERIAL_HPP__ */
