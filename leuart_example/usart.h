#ifndef __USART__
#define __USART__

void init_usart1();
void usart1_transfer(char* ch, size_t len);

#define USART_CLK  (PB7)
#define USART_MISO (PC1)
#define USART_MOSI (PC0)
#define USART_SS   (PB8)

#endif
