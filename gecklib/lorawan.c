#include <stdlib.h>

#include "lorawan.h"
#include "aes.h"

// JoinNonce | JoinEUI | DevNonce


// aes128_encrypt(AppKey, 0x02 | JoinNonce | JoinEUI | DevNonce | pad16)
void lorawan_derieve_key(
    // uint8_t *der_key,
    // uint8_t *root_key,
    uint8_t key_id,
    uint8_t join_nonce[LORAWAN_JOIN_NONCE_SIZE],
    uint8_t join_eui[LORAWAN_JOIN_EUI_SIZE]
) {
    uint8_t pt[AES128_BLOCKSIZE] = {0};
    pt[0] = key_id;

    for (size_t i = 1; i < LORAWAN_JOIN_NONCE_SIZE + 1; i++)
        pt[i] = join_nonce[i];

    for (size_t i = 4; i < LORAWAN_JOIN_EUI_SIZE + 4; i++)
        pt[i] = join_eui[i];

    aes128_encrypt(pt, pt, NULL);

}
