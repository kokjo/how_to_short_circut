#include <stdint.h>

#include "mcu.h"
#include "spi.h"

void spi_bitbang_begin_transaction(struct spi_interface *_iface){
    struct spi_bitbang *iface = (struct spi_bitbang *) _iface;
    gpio_clr(iface->cs_pin);
}

void spi_bitbang_end_transaction(struct spi_interface *_iface){
    struct spi_bitbang *iface = (struct spi_bitbang *) _iface;
    gpio_set(iface->cs_pin);
}

uint8_t spi_bitbang_transfer_byte(struct spi_interface *_iface, uint8_t byte){
    struct spi_bitbang *iface = (struct spi_bitbang *) _iface;
    uint8_t bit;
    for(bit = 0x80; bit; bit >>= 1){
        gpio_dout(iface->mosi_pin, byte & bit);
        delay(iface->delay);
        gpio_set(iface->clk_pin);
        byte &= ~bit;
        if(gpio_input(iface->miso_pin)) byte |= ~bit;
        gpio_clr(iface->clk_pin);
    }
    return byte;
}
