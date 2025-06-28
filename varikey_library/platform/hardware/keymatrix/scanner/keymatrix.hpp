#pragma once

#include <cstdbool>
#include <cstdint>

#include "pico/stdlib.h"

void keymatrix_init(void);
void keymatrix_scan(void);
void keymatrix_events(void);
