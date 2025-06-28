
#include <cstdio>
#include <cstring>

#include <pico/time.h>

#include "keymatrix.hpp"
#include "keymatrix_queue.hpp"

#define NUM_COLS 5
#define NUM_ROWS 3
#define DEBOUNCE_TICKS 0

const uint8_t row_pins[NUM_ROWS] = {2, 3, 4};
const uint8_t col_pins[NUM_COLS] = {17, 18, 19, 20, 21};

uint8_t debounce_counter[NUM_ROWS][NUM_COLS] = {0};

bool key_now[NUM_ROWS][NUM_COLS] = {0};
bool key_last[NUM_ROWS][NUM_COLS] = {0};

void keymatrix_init(void)
{
    for (int r = 0; r < NUM_ROWS; ++r)
    {
        gpio_init(row_pins[r]);
        gpio_set_dir(row_pins[r], GPIO_OUT);
        gpio_put(row_pins[r], 0);
    }
    for (int c = 0; c < NUM_COLS; ++c)
    {
        gpio_init(col_pins[c]);
        gpio_set_dir(col_pins[c], GPIO_IN);
        gpio_pull_down(col_pins[c]);
    }
}

void keymatrix_scan(void)
{
    for (int r = 0; r < NUM_ROWS; ++r)
    {
        gpio_put(row_pins[r], 1);
        sleep_us(5);
        
        for (int c = 0; c < NUM_COLS; ++c)
        {
            // printf("row=%d col=%d\n", r, c);

            const bool status = (gpio_get(col_pins[c]) == 1);
            gpio_put(25, status);

            // if (status)
            // {
            //     printf("TASTE! row=%d col=%d\n", r, c);
            // }

            const bool previous = key_now[r][c];

            if (status != previous)
            {
                //printf("row%d col%d is%d\n", c + 1, r + 1, status);
                debounce_counter[r][c]++;
                if (debounce_counter[r][c] >= DEBOUNCE_TICKS)
                {
                    key_now[r][c] = status;
                    //printf("KEY S%d R%d C%d\n", status, r + 1, c + 1);

                    debounce_counter[r][c] = 0;
                }
            }
            else
            {
                debounce_counter[r][c] = 0;
            }
        }

        gpio_put(row_pins[r], 0);


        // Aktives Entladen: alle COLs kurz auf Output und 0
        for (int c = 0; c < NUM_COLS; ++c)
        {
            gpio_set_dir(col_pins[c], GPIO_OUT);
            gpio_put(col_pins[c], 0);
        }
        sleep_us(10); // gib C Zeit zum Entladen (Wert ggf. anpassen)

        // Danach wieder Input und Pull-Down aktivieren
        for (int c = 0; c < NUM_COLS; ++c)
        {
            gpio_set_dir(col_pins[c], GPIO_IN);
            gpio_pull_down(col_pins[c]);
        }


        sleep_us(5);
    }
}

void keymatrix_events(void)
{
    for (uint8_t c = 0; c < NUM_COLS; ++c)
    {
        for (uint8_t r = 0; r < NUM_ROWS; ++r)
        {
            const uint8_t col_idx = static_cast<uint8_t>(c + 1);
            const uint8_t row_idx = static_cast<uint8_t>(r + 1);

            const bool now = key_now[r][c];
            const bool last = key_last[r][c];

            if (now != last)
            {
                key_last[r][c] = now; // ← wichtig: sofort aktualisieren

                keymatrix::KeyEvent::Type type = now ? keymatrix::KeyEvent::Type::PRESS : keymatrix::KeyEvent::Type::RELEASE;
                keymatrix::push_event(type, col_idx, row_idx);

            }
            /*
            if (key_now[r][c])
            {
                printf("KEY PRESSED R%d C%d\n", r + 1, c + 1);
                keymatrix::KeyEvent event = {
                    keymatrix::KeyEvent::PRESS,
                    col_idx,
                    row_idx,
                };
                push_event(event);
            }
            else
            {
                printf("KEY RELEASED R%d C%d\n", r + 1, c + 1);
                keymatrix::KeyEvent event = {
                    keymatrix::KeyEvent::RELEASE,
                    col_idx,
                    row_idx,
                };
                push_event(event);
            }
            */
        }
    }
}
