#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "em_device.h"

static uint32_t* aes_output32;
static volatile bool aes_finished = true;

void AES_IRQHandler(void) {
    AES->IFC = AES_IFC_DONE;

    for (int i = 3; i >= 0; i--)
        aes_output32[i] = __REV(AES->DATA);

    aes_finished = false;
}

void aes(
    uint8_t *output,
    const uint8_t *key,
    const uint8_t *input,
    bool decrypt
) {

    // wait for any ongoing aes operation

    while (!aes_finished);
    aes_finished = false;

    AES->CTRL =
        decrypt << _AES_CTRL_DECRYPT_SHIFT |
        AES_CTRL_DATASTART;

    // clear and enable AES interrupt

    // AES->IFC = AES_IFC_DONE;
    // AES->IEN = AES_IEN_DONE;
    // NVIC_EnableIRQ(AES_IRQn);
    // AES_CTRL_AES256 |

    for (int i = 3; i >= 0; i--)
        AES->KEYLA = __REV(((uint32_t*) key) [i]);
        // AES->KEYLA = __REV(((uint32_t*) key) [i]);

    for (int i = 3; i >= 0; i--)
        AES->DATA = __REV(((uint32_t*) input)[i]);

    // wait for operation

    while (AES->STATUS & AES_STATUS_RUNNING);

    for (int i = 3; i >= 0; i--)
        ((uint32_t*) output) [i] = __REV(AES->DATA);

    aes_finished = true;
}

void aes128_encrypt(
    uint8_t *output,
    const uint8_t *key,
    const uint8_t *input
) {
    aes(output, key, input, false);
}

void aes128_decrypt(
    uint8_t *output,
    const uint8_t *key,
    const uint8_t *input
) {
    aes(output, key, input, true);
}

