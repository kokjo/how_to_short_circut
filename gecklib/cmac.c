

#include <stdint.h>
#include <stdlib.h>

#include "aes.h"
#include "cmac.h"

/* shift a block and output the carry bit
 */
uint8_t shift1(
    uint8_t v[AES128_KEYSIZE]
) {
    uint8_t t;
    uint8_t c = 0;
    size_t i = 15;

    do {
        t = v[i] >> 7;
        v[i] <<= 1;
        v[i] |= c;
        c = t;
    } while (i--);

    return c;
}

void aes128_cmac(
    uint8_t tag[AES128_BLOCKSIZE],
    uint8_t key[AES128_KEYSIZE],
    uint8_t *data,
    size_t len
) {

    // null tag

    for (size_t i = 0; i < AES128_BLOCKSIZE; i++)
        tag[i] = 0;

    // tag all but last block

    while (len > AES128_BLOCKSIZE) {
        for (size_t i = 0; i < AES128_BLOCKSIZE; i++)
            tag[i] ^= *(data++);
        aes128_encrypt(tag, key, tag);
        len -= AES128_BLOCKSIZE;
    }

    for (size_t i = 0; i < len; i++)
        tag[i] ^= data[i];

    // derieve and add tag key

    uint8_t kt[AES128_KEYSIZE];
    uint8_t const_zero[AES128_BLOCKSIZE] = {0};
    aes128_encrypt(kt, key, const_zero);

    if (shift1(kt))
        kt[15] ^= 0x87;

    if (len < AES128_BLOCKSIZE) {
        tag[len] ^= 0x80; // pad
        if (shift1(kt))
            kt[15] ^= 0x87;
    }

    for (size_t i = 0; i < AES128_BLOCKSIZE; i++)
        tag[i] ^= kt[i];

    aes128_encrypt(tag, key, tag);
}
