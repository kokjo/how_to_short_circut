#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include "mcu.h"
#include "gpio.h"
#include "leuart.h"
#include "printf.h"

#define _CLKDIV (616) // baudrate 9600

void init_leuart0(){
    /* Set clock divisor */
    LEUART0->CLKDIV = _CLKDIV;

    /* Route and enable pins */
    LEUART0->ROUTE = LEUART0_LOCATION;
    if(LEUART0_ENABLE_RX) LEUART0->ROUTE |= LEUART_ROUTE_RXPEN;
    if(LEUART0_ENABLE_TX) LEUART0->ROUTE |= LEUART_ROUTE_TXPEN;
    LEUART0->CMD = LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX;
    LEUART0->CTRL = LEUART_CTRL_STOPBITS_TWO;

    /* TX set as PUSHPULL */
    gpio_mode(LEUART0_TX, GPIO_MODE_PUSHPULL);

    /* RX set as INPUTPULL and set pullup */
    gpio_mode(LEUART0_RX, GPIO_MODE_INPUTPULL);
    gpio_set(LEUART0_RX);

    /* Enable leuart0 */
    if(LEUART0_ENABLE_RX) LEUART0->CMD = LEUART_CMD_RXEN;
    if(LEUART0_ENABLE_TX) LEUART0->CMD = LEUART_CMD_TXEN;
}

void _leuart0_out(struct output *o, char ch){
    o = o;
    while(!(LEUART0->STATUS & LEUART_STATUS_TXBL)){ }; // WAIT
    LEUART0->TXDATA = ((uint32_t)ch) & 0xffUL;
}

void leuart0_putchar(char ch){
    _leuart0_out(NULL, ch);
}

void leuart0_puts(char *s){
    leuart0_printf("%s\n", s);
}

const struct output leuart0_output = {
    .out = _leuart0_out
};

void leuart0_printf(const char *fmtstr, ...){
    va_list va;
    
    va_start(va, fmtstr);
    va_printf((struct output *)&leuart0_output, fmtstr, va);
}
