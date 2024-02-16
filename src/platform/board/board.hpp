/**
 * \file board.hpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#ifndef __PLATFORM_BOARD_HPP__
#define __PLATFORM_BOARD_HPP__

#include "backlight_color.hpp"
#include "board_defines.hpp"
#include "board_keypad.hpp"

extern void board_initialize();
extern void board_shutdown();
extern void board_perform();

extern const uint64_t get_stopwatch(void);

extern void ticker_start(platform::board::ticker_handler_t);
extern void ticker_stop(void);

extern const float get_temperature(void);
extern const uint16_t get_temperature_raw(void);

extern void set_backlight(const engine::backlight::color_t &, const engine::backlight::color_t &);

extern const platform::board::DIRECTION get_gpio_direction(const platform::board::IDENTIFIER);
extern void set_gpio_direction(const platform::board::IDENTIFIER, platform::board::DIRECTION);
extern void enable_gpio_event(platform::board::callback_t, const bool);
extern const platform::board::VALUE get_value(const platform::board::IDENTIFIER);
extern void set_value(const platform::board::IDENTIFIER, const bool);

extern void display_symbol(uint8_t const page_start, uint8_t const page_end,
                           uint8_t const column_start, uint8_t const column_end,
                           uint8_t const *const data, size_t const len);
extern void display_clean();

#endif // __PLATFORM_BOARD_HPP__
