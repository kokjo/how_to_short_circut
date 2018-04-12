#ifndef LEUART_H
#define LEUART_H

#include "config.h"

void init_leuart0();
void leuart0_putchar(char ch);
char leuart0_getchar();
void leuart0_puts(char *s);
void leuart0_printf(const char *fmtstr, ...);

#if LEUART0_LOCATION == LEUART_ROUTE_LOCATION_LOC1
    #define LEUART0_RX (PB14)
    #define LEUART0_TX (PB13)
#elif LEUART0_LOCATION == LEUART_ROUTE_LOCATION_LOC3
    #define LEUART0_RX (PF1)
    #define LEUART0_TX (PF0)
#elif LEUART0_LOCATION == LEUART_ROUTE_LOCATION_LOC4
    #define LEUART0_RX (PA0)
    #define LEUART0_TX (PF2)
#elif LEUART0_LOCATION == LEUART_ROUTE_LOCATION_LOC5
    #define LEUART0_RX (PC15)
    #define LEUART0_TX (PC14)
#else
    #error "Fix leuart.h"
#endif

#endif
