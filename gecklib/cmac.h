#ifndef __HEADER_CMAC__
#define __HEADER_CMAC__

#include <stdint.h>
#include <stdlib.h>
#include "aes.h"

#define CMAC_TAG_SIZE (AES128_BLOCK_SIZE)

void aes128_cmac(
    uint8_t tag[AES128_BLOCKSIZE],
    uint8_t key[AES128_KEYSIZE],
    uint8_t data[],
    size_t len
);

#endif
