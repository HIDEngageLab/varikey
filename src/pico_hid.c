#include <hardware/watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "engine.h"
#include "hid.h"
#include "pico_hid.h"

static bool running = false;

/*------------- MAIN -------------*/
int main(void)
{
    board_init();
    tusb_init();

    while (1)
    {
        tud_task(); // tinyusb device task
        hid_task();
    }

    return 0;
}

extern void composed_hid_device_shutdown(void)
{
    running = false;

    engine_shutdown();

    // usart_shutdown();

    sleep_ms(200);

    watchdog_enable(0, false);
    while (true)
        ;
}
