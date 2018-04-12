#include "mcu.h"

void init_watchdog(void) {
    // disable the watchdog timer
    WDOG->CTRL = 0;
}
