#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "em_device.h"
#include "gpio.h"
#include "leuart.h"

#define _CLKDIV (616) // baudrate 9600

void init_leuart0(){
    /* Set clock divisor */
    LEUART0->CLKDIV = _CLKDIV;

    /* Route: TX = PB13 and RX = PB14 */
    LEUART0->ROUTE = LEUART_ROUTE_LOCATION_LOC1 | LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN;
    LEUART0->CMD = LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX | LEUART_CMD_RXEN | LEUART_CMD_TXEN;
    LEUART0->CTRL = LEUART_CTRL_STOPBITS_TWO;

    /* PB13 set as PUSHPULL */
    gpio_mode(PB13, GPIO_MODE_PUSHPULL);

    /* PB14 set as INPUTPULL and set pullup */
    gpio_mode(PB14, GPIO_MODE_INPUTPULL);
    gpio_set(PB14);
    
    /* enable leuart0 */
    LEUART0->CMD = LEUART_CMD_RXEN | LEUART_CMD_TXEN;
}

void leuart0_putchar(char ch){
    while (!(LEUART0->STATUS & LEUART_STATUS_TXBL)){ } // WAIT

    LEUART0->TXDATA = (uint32_t)ch & 0xffUL;
}

void leuart0_puts(char *s){
    int i;
    for(i = 0; s[i]; i += 1) leuart0_putchar(s[i]);
    leuart0_putchar('\n');
}

char hexchars[] = "0123456789abcdef";

void leuart0_printf(char *fmtstr, ...){
    va_list valist;
    int escape = 0;
    char *str;
    unsigned int num;

    va_start(valist, fmtstr);
    while(*fmtstr){
        if(escape){
            escape = 0;
            switch(*fmtstr){
                case '%':
                    leuart0_putchar('%');
                    break;
                case 's':
                    str = va_arg(valist, char *);
                    while(*str) leuart0_putchar(*str++);
                    break;
                case 'p':
                    leuart0_putchar('0');
                    leuart0_putchar('x');
                case 'x':
                    num = va_arg(valist, unsigned int);
                    leuart0_putchar(hexchars[(num >> 28) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 24) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 20) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 16) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 12) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 8) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 4) & 0xf]);
                    leuart0_putchar(hexchars[(num >> 0) & 0xf]);
                    break;
            }
        } else if(*fmtstr == '%'){
            escape = 1;
        } else {
            leuart0_putchar(*fmtstr); 
        }
        fmtstr++;
    }
}
