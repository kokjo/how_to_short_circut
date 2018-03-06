#ifndef LEUART_H
#define LEUART_H

void init_leuart0();
void leuart0_putchar(char ch);
void leuart0_puts(char *s);
void leuart0_printf(char *fmtstr, ...);

#endif
