/**
 * \file varikey.hpp
 * \author Roman Koch
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __VARIKEY_DEVICE_HPP__
#define __VARIKEY_DEVICE_HPP__

extern void varikey_initialize(void);
extern void varikey_shutdown(void);

extern void varikey_reboot(void);
extern void varikey_bootsel(void);

#endif /* __VARIKEY_DEVICE_HPP__ */
