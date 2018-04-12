#include <stdint.h>

#include "mcu.h"

void usart0_init() {
    USART0->CTRL = 0;
    USART0->CTRL = USART_CTRL_SYNC | USART_CTRL_MSBF;

    USART0->FRAME = 0;
    USART0->FRAME = USART_FRAME_DATABITS_EIGHT;

    USART0->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN;

    USART0->ROUTE = USART0_LOCATION;
    USART0->ROUTE |= USART_ROUTE_CLKPEN;
    USART0->ROUTE |= USART_ROUTE_TXPEN;
    USART0->ROUTE |= USART_ROUTE_RXPEN;

    gpio_mode(USART0_CLK, GPIO_MODE_PUSHPULL);
    gpio_mode(USART0_MISO, GPIO_MODE_INPUT);
    gpio_mode(USART0_MOSI, GPIO_MODE_PUSHPULL);
}

uint8_t usart0_transfer_byte(uint8_t data){
        while (!(USART0->STATUS & USART_STATUS_TXBL)){} // WAIT
        USART0->TXDATA = (uint32_t)(data) & 0xffUL;
        while (!(USART0->STATUS & USART_STATUS_RXDATAV)){} // WAIT
        return (uint8_t) USART0->RXDATA & 0xffUL;
}

void usart0_transfer(uint8_t* data, size_t len) {
    size_t i;
    USART0->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    for (i = 0; i < len; i++) {
        data[i] = usart0_transfer_byte(data[i]);
    }
}
