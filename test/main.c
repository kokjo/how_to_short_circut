#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "util.h"

#include "em_device.h"
#include "toboot-api.h"
#include "gpio.h"
#include "leuart.h"
#include "usart.h"

#include "rfm95.h"
#include "printf.h"

#define GREEN PB7
#define RED PA0

#define SS_PIN  (PB11)
#define RST_PIN (PB14)

#define RECV (1)

void main(){
    gpio_mode(SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(SS_PIN);
    gpio_mode(RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(RST_PIN);

    delay(1000);
    leuart0_printf("EFM32HG309 SPI LEUART BRIDGE\n");

    struct rfm95_t conf;

    conf.freq = 868000000;
    conf.bw = MC1_BW_125kHz;
    conf.cr = MC1_CR_45;
    conf.sf = MC2_SF_128;

    conf.pin_ss = SS_PIN;
    conf.pin_rst = RST_PIN;

    char msg[256];

    for (unsigned int i = 0; i < 10000; i++) {

        rfm95_update_config(&conf);

        // dump regs

        /*
        for (unsigned int n = 0; n < 0xf7; n++) {
            for (int n = 0; n < 256; n++)
                msg[n] = 0;
            sprintf(msg, "reg[%hhx] = %hhx\n", n, rfm95_read_reg(&conf, n));
            leuart0_printf(msg);
        }
        */

#ifdef RECV

        // dump memory

        for (int n = 0; n < 256; n++)
            msg[n] = 0;

        rfm95_recv(&conf, (uint8_t*) msg);
        rfm95_read_memory(&conf, 0, (uint8_t*) msg, 16);
        leuart0_printf(msg);
        leuart0_printf("\n");

#else
        for (int n = 0; n < 256; n++)
            msg[n] = 0;

        sprintf(msg, "HELLO LoRa %x\n", i);
        leuart0_printf(msg);
        rfm95_send(&conf, (uint8_t*) msg, 16);
#endif

        delay(2000);
    }
}
