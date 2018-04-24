#ifndef __HEADER_AES__
#define __HEADER_AES__

#include <stdint.h>

#define AES128_KEYSIZE (16)
#define AES128_BLOCKSIZE (16)

void AES_Handler(void);

void aes128_decrypt(
    uint8_t *output,
    const uint8_t *key,
    const uint8_t *input
);

void aes128_encrypt(
    uint8_t *output,
    const uint8_t *key,
    const uint8_t *input
);

#endif
