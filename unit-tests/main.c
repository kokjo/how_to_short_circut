#include <stdint.h>
#include <stdbool.h>

#include "aes.h"
#include "cmac.h"

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
#define RST_PIN (PC1)

// #define RECV (1)

void assert(bool v, char* s) {
    if (!v)
        leuart0_printf(s);
}

void assert_str(uint8_t *s1, uint8_t *s2, size_t len, char* s) {
    for (size_t i = 0; i < len; i++)
        if (s1[i] != s2[i]) {
            leuart0_printf("%s : failed\n", s);
            break;
        }
    leuart0_printf("%s : success\n", s);
}

void main(){
    gpio_mode(SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(SS_PIN);
    gpio_mode(RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(RST_PIN);

    delay(1000);
    leuart0_printf("EFM32HG309 Encryption\n");

    for (unsigned int i = 0; i < 10000; i++) {

        {
            uint8_t key[16] = {
                0x2b, 0x7e, 0x15, 0x16,
                0x28, 0xae, 0xd2, 0xa6,
                0xab, 0xf7, 0x15, 0x88,
                0x09, 0xcf, 0x4f, 0x3c
            };


            {
                uint8_t ct[16];
                uint8_t pt[16] = {
                    0x6b, 0xc1, 0xbe, 0xe2,
                    0x2e, 0x40, 0x9f, 0x96,
                    0xe9, 0x3d, 0x7e, 0x11,
                    0x73, 0x93, 0x17, 0x2a
                };

                uint8_t ctE[] =  {
                    0x3a, 0xd7, 0x7b, 0xb4,
                    0x0d, 0x7a, 0x36, 0x60,
                    0xa8, 0x9e, 0xca, 0xf3,
                    0x24, 0x66, 0xef, 0x97
                };

                aes128_encrypt(ct, key, pt);
                assert_str(ct, ctE, sizeof(ctE), "AES128");
            }

            uint8_t tag[16];

            {
                uint8_t tagE[] = {
                    0xbb, 0x1d, 0x69, 0x29,
                    0xe9, 0x59, 0x37, 0x28,
                    0x7f, 0xa3, 0x7d, 0x12,
                    0x9b, 0x75, 0x67, 0x46
                };

                aes128_cmac(tag, key, NULL, 0);
                assert_str(tag, tagE, sizeof(tagE), "CMAC-TAG-0");
            }

            {
                uint8_t msg[] = {
                    0x6b, 0xc1, 0xbe, 0xe2,
                    0x2e, 0x40, 0x9f, 0x96,
                    0xe9, 0x3d, 0x7e, 0x11,
                    0x73, 0x93, 0x17, 0x2a
                };

                uint8_t tagE[] = {
                    0x07, 0x0a, 0x16, 0xb4,
                    0x6b, 0x4d, 0x41, 0x44,
                    0xf7, 0x9b, 0xdd, 0x9d,
                    0xd0, 0x4a, 0x28, 0x7c
                };

                aes128_cmac(tag, key, msg, sizeof(msg));
                assert_str(tag, tagE, sizeof(tagE), "CMAC-TAG-16");
            }

            {
                uint8_t msg[] = {
                    0x6b, 0xc1, 0xbe, 0xe2,
                    0x2e, 0x40, 0x9f, 0x96,
                    0xe9, 0x3d, 0x7e, 0x11,
                    0x73, 0x93, 0x17, 0x2a,
                    0xae, 0x2d, 0x8a, 0x57,
                    0x1e, 0x03, 0xac, 0x9c,
                    0x9e, 0xb7, 0x6f, 0xac,
                    0x45, 0xaf, 0x8e, 0x51,
                    0x30, 0xc8, 0x1c, 0x46,
                    0xa3, 0x5c, 0xe4, 0x11
                };

                uint8_t tagE[] = {
                    0xdf, 0xa6, 0x67, 0x47,
                    0xde, 0x9a, 0xe6, 0x30,
                    0x30, 0xca, 0x32, 0x61,
                    0x14, 0x97, 0xc8, 0x27
                };

                aes128_cmac(tag, key, msg, sizeof(msg));
                assert_str(tag, tagE, sizeof(tagE), "CMAC-TAG-40");
            }
        }

        delay(1000);
    }
}
