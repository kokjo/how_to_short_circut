#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>

struct spi_interface;

typedef uint8_t (*spi_transfer_byte_t)(struct spi_interface *, uint8_t);
typedef void (*spi_begin_transaction_t)(struct spi_interface *);
typedef void (*spi_end_transaction_t)(struct spi_interface *);

struct spi_interface {
    spi_transfer_byte_t transfer_byte;
    spi_begin_transaction_t begin_transaction;
    spi_end_transaction_t end_transaction;
};

struct spi_bitbang {
    struct spi_interface iface;
    uint8_t cs_pin;
    uint8_t clk_pin;
    uint8_t miso_pin;
    uint8_t mosi_pin;
    uint8_t delay;
};

#endif
