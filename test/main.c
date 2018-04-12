#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "util.h"

#include "em_device.h"
#include "toboot-api.h"
#include "gpio.h"
#include "leuart.h"
#include "usart.h"

#define GREEN PB7
#define RED PA0

#define SS_PIN  (PB11)
#define RST_PIN (PB14)

void main(){
    char ch;
    int num = 0;
    uint8_t data = 0;

    gpio_mode(SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(SS_PIN);
    gpio_mode(RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(RST_PIN);

    delay(1000);
    leuart0_printf("EFM32HG309 SPI LEUART BRIDGE\n");

    while(1){
        ch = leuart0_getchar();
        switch(ch){
            case '?':
                leuart0_printf("EFM32HG309 SPI LEUART BRIDGE\n");
                num = 0;
                data = 0;
                break;
            case '/':  gpio_set(SS_PIN);  break;
            case '\\': gpio_clr(SS_PIN);  break;
            case 'R':  gpio_set(RST_PIN); break;
            case 'r':  gpio_clr(RST_PIN); break;
            default:
                if('0' <= ch && ch <= '9'){
                    data = (data << 4) | ((ch - '0') + 0x0);
                    num++;
                }
                if('a' <= ch && ch <= 'f'){
                    data = (data << 4) | ((ch - 'a') + 0xa);
                    num++;
                }
                if('A' <= ch && ch <= 'F'){
                    data = (data << 4) | ((ch - 'A') + 0xa);
                    num++;
                }
                if(num == 2){
                    data = usart0_transfer_byte(data);
                    num = 0;
                    leuart0_printf("%hhx",data);
                }
        }
    }
}
