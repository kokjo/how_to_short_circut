#include <stdint.h>
#include <stdlib.h>

#include "gpio.h"
#include "util.h"
#include "rfm95.h"

// Helper Functions

void spi_transfer(struct rfm95_t *c, uint8_t *data, size_t len){
    gpio_clr(c->pin_ss);
    usart0_transfer(data, len);
    gpio_set(c->pin_ss);
    delay(1);
}

uint8_t rfm95_write_reg(struct rfm95_t *c, uint8_t reg, uint8_t val){
    uint8_t data[2] = {(reg & 0x7f) | 0x80, val};
    spi_transfer(c, data, sizeof(data));
    return data[1];
}

uint8_t rfm95_read_reg(struct rfm95_t *c, uint8_t reg){
    uint8_t data[2] = {reg & 0x7f, 0x00};
    spi_transfer(c, data, sizeof(data));
    return data[1];
}

void rfm95_read_fifo(struct rfm95_t *c, uint8_t *data, size_t len){
    gpio_clr(c->pin_ss);
    usart0_transfer_byte(RFM95_FIFO);
    usart0_transfer(data, len);
    gpio_set(c->pin_ss);
}

void rfm95_write_fifo(struct rfm95_t *c, uint8_t *data, size_t len){
    gpio_clr(c->pin_ss);
    usart0_transfer_byte(RFM95_FIFO | 0x80);
    usart0_transfer(data, len);
    gpio_set(c->pin_ss);
}

void rfm95_read_memory(struct rfm95_t *c, uint8_t addr, uint8_t *data, size_t len){
    rfm95_write_reg(c, RFM95_FIFO_ADDR, addr);
    rfm95_read_fifo(c, data, len);
}

void rfm95_write_memory(struct rfm95_t *c, uint8_t addr, uint8_t *data, size_t len){
    rfm95_write_reg(c, RFM95_FIFO_ADDR, addr);
    rfm95_write_fifo(c, data, len);
}

// Exposed API

void rfm95_update_config(struct rfm95_t *c) {

    // reset

    gpio_clr(c->pin_rst);
    delay(1);
    gpio_set(c->pin_rst);
    delay(1);

    // enter LoRa mode & stdby

    rfm95_write_reg(c, RFM95_OPMODE, RFM95_OPMODE_LORA | RFM95_OPMODE_SLEEP);
    delay(1);

    rfm95_write_reg(c, RFM95_OPMODE, RFM95_OPMODE_LORA | RFM95_OPMODE_STANDBY);
    delay(1);

    // set frequency

    uint32_t frf = (uint32_t) ((((uint64_t)(c->freq)) << 19ULL) / 32000000ULL);
    rfm95_write_reg(c, RFM95_FRF_MSB, (frf >> 16) & 0xff);
    rfm95_write_reg(c, RFM95_FRF_MID, (frf >> 8) & 0xff);
    rfm95_write_reg(c, RFM95_FRF_LSB, frf & 0xff);

    // modem config

    rfm95_write_reg(c, RFM95_MODEM_CONFIG1, c->bw | c->cr);
    rfm95_write_reg(c, RFM95_MODEM_CONFIG2, c->sf);

    // power config (TODO: make configuarable)

    rfm95_write_reg(c, RFM95_PACONFIG, 0xf2);
    rfm95_write_reg(c, RFM95_PARAMP, 0x08);

}

void rfm95_send(struct rfm95_t *c, uint8_t* msg, uint8_t len) {

    // write payload to fifo

    rfm95_write_reg(c, RFM95_TXBASE, 0);
    rfm95_write_memory(c, 0, msg, len);

    // set length and start transmission

    rfm95_write_reg(c, RFM95_PAYLOAD_LENGTH, len);
    rfm95_write_reg(c, RFM95_OPMODE, RFM95_OPMODE_LORA | RFM95_OPMODE_TX);
}

uint8_t rfm95_recv(struct rfm95_t *c, uint8_t* msg) {
    rfm95_write_reg(c, RFM95_RXBASE, 0);
    rfm95_write_reg(c, RFM95_OPMODE, RFM95_OPMODE_LORA | RFM95_OPMODE_RX);
    msg = msg;
    return 0;
}
