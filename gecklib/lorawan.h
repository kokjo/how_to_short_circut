#ifndef __HEADER_LORAWAN__
#define __HEADER_LORAWAN__

#include <stdint.h>
#include "aes.h"

#define LORAWAN_JOIN_EUI_SIZE   (8)
#define LORAWAN_JOIN_NONCE_SIZE (3)

#define LORAWAN_DEV_EUI_SIZE    (8)
#define LORAWAN_DEV_NONCE_SIZE  (2)

/* All LoRa values are encoded in little-endian
 */

struct lorawan_root_keys_t {
    uint8_t NwkKey[AES128_KEYSIZE]; // Network Key
    uint8_t AppKey[AES128_KEYSIZE]; // Application Key
};

struct lorawan_derived_keys_t {

    // Application keys

    uint8_t AppSKey[AES128_KEYSIZE]; // Application session key

    // Network Keys

    uint8_t NwkSEncKey[AES128_KEYSIZE];  // Network session encryption key
    uint8_t FNwkSIntKey[AES128_KEYSIZE]; // Forwarding Network session integrity key
    uint8_t SNwkSIntKey[AES128_KEYSIZE]; // Serving Network session integrity key
};

struct lorawan_config_t {
    struct lorawan_root_keys_t keys;
};

struct lorawan_state_t {
    struct lorawan_derived_keys_t keys;



    uint32_t DevAddr;
};

struct __attribute__((__packed__)) lorawan_msg_join_request {
    uint8_t join_eui[LORAWAN_JOIN_EUI_SIZE];
    uint8_t dev_eui[LORAWAN_DEV_EUI_SIZE];
    uint8_t dev_nonce[LORAWAN_DEV_NONCE_SIZE];
};

#endif
