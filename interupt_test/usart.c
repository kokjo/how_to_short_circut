#include "em_device.h"
#include "gpio.h"

#include "usart.h"

void init_usart1() {
    USART1->CTRL = 0;
    USART1->CTRL = USART_CTRL_SYNC | USART_CTRL_MSBF;

    USART1->FRAME = 0;
    USART1->FRAME = USART_FRAME_DATABITS_EIGHT;

    USART1->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    USART1->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN;

    USART1->ROUTE = USART_ROUTE_LOCATION_LOC0 | USART_ROUTE_CLKPEN | USART_ROUTE_TXPEN | USART_ROUTE_RXPEN;

    gpio_mode(USART_CLK, GPIO_MODE_PUSHPULL);
    gpio_mode(USART_MISO, GPIO_MODE_INPUT);
    gpio_mode(USART_MOSI, GPIO_MODE_PUSHPULL);
    gpio_mode(USART_SS, GPIO_MODE_PUSHPULL);
}

void usart1_transfer(char* ch, size_t len) {
    USART1->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    for (size_t i = 0; i < len; i++) {
        while (!(USART1->STATUS & USART_STATUS_TXBL)){} // WAIT
        USART1->TXDATA = (uint32_t)(ch[i]) & 0xffUL;
        while (!(USART1->STATUS & USART_STATUS_RXDATAV)){} // WAIT
        ch[i] = (char) USART1->RXDATA & 0xffUL;
    }
}
