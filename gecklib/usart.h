#ifndef __USART__
#define __USART__

#include <stdint.h>

#include "mcu.h"

void init_usart0();
uint8_t usart0_transfer_byte(uint8_t data);
void usart0_transfer(uint8_t* ch, size_t len);

#define USART0_LOCATION USART_ROUTE_LOCATION_LOC4

#if USART0_LOCATION == USART_ROUTE_LOCATION_LOC3
    #define USART0_CLK  (PC15)
    #define USART0_SS   (PC14)
    #define USART0_MISO (PE12)
    #define USART0_MOSI (PE13)
#elif USART0_LOCATION == USART_ROUTE_LOCATION_LOC4
    #define USART0_CLK  (PB13)
    #define USART0_SS   (PB14)
    #define USART0_MISO (PB8)
    #define USART0_MOSI (PB7)
#elif USART0_LOCATION == USART_ROUTE_LOCATION_LOC5
    #define USART0_CLK  (PB13)
    #define USART0_SS   (PB14)
    #define USART0_MISO (PC1)
    #define USART0_MOSI (PC0)
#elif USART0_LOCATION == USART_ROUTE_LOCATION_LOC6
    #define USART0_CLK  (PE12)
    #define USART0_SS   (PE13)
    #define USART0_MISO (PC1)
    #define USART0_MOSI (PC0)
#else
    #error "PLEASE fix usart.h"
#endif

#endif
