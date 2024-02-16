/**
 * \file board.cpp
 * \author Koch, Roman (koch.roman@googlemail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "board.hpp"

platform::board::BoardKeypad board;

extern void board_initialize()
{
    board.initialize();
}

extern void board_shutdown()
{
    board.shutdown();
}

extern void board_perform()
{
    board.perform();
}

extern const uint64_t get_stopwatch(void)
{
    return board.soc.get_stopwatch();
}

extern void ticker_start(platform::board::ticker_handler_t _handler)
{
    board.soc.ticker_start(_handler);
}

extern void ticker_stop(void)
{
    board.soc.ticker_stop();
}

extern const float get_temperature(void)
{
    return board.soc.get_temperature();
}

extern const uint16_t get_temperature_raw(void)
{
    return board.soc.get_temperature_raw();
}

extern void set_backlight(const engine::backlight::color_t &_left, const engine::backlight::color_t &_right)
{
    board.backlight.set_backlight(_left, _right);
}

extern const platform::board::DIRECTION get_gpio_direction(const platform::board::IDENTIFIER _value)
{
    return board.soc.get_gpio_direction(_value);
}

extern void set_gpio_direction(const platform::board::IDENTIFIER _identifier, platform::board::DIRECTION _direction)
{
    board.soc.set_gpio_direction(_identifier, _direction);
}

extern void enable_gpio_event(platform::board::callback_t _callback, const bool _value)
{
    board.soc.enable_gpio_event(_callback, _value);
}

extern const platform::board::VALUE get_value(const platform::board::IDENTIFIER _identifier)
{
    return board.soc.get_value(_identifier);
}

extern void set_value(const platform::board::IDENTIFIER _identifier, const bool _value)
{
    board.soc.set_value(_identifier, _value);
}

extern void display_symbol(uint8_t const page_start, uint8_t const page_end,
                           uint8_t const column_start, uint8_t const column_end,
                           uint8_t const *const data, size_t const len)
{
    board.display.symbol(page_start, page_end, column_start, column_end, data, len);
}

extern void display_clean()
{
    board.display.clean();
}
