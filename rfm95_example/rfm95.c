#include <stdint.h>
#include <stddef.h>

#include "mcu.h"
#include "rfm95.h"

void delay(int);

void spi_transfer(uint8_t *data, size_t len){
    gpio_clr(RFM95_SS_PIN);
    usart0_transfer(data, len);
    gpio_set(RFM95_SS_PIN);
    delay(1);
}

uint8_t rfm95_read_reg(uint8_t reg){
    uint8_t data[2] = {reg & 0x7f, 0x00};
    spi_transfer(data, sizeof(data));
    return data[1];
}

uint8_t rfm95_write_reg(uint8_t reg, uint8_t val){
    uint8_t data[2] = {(reg & 0x7f) | 0x80, val};
    spi_transfer(data, sizeof(data));
    return data[1];
}

void rfm95_read_fifo(uint8_t *data, size_t len){
    gpio_clr(RFM95_SS_PIN);
    usart0_transfer_byte(RFM95_FIFO);
    usart0_transfer(data, len);
    gpio_set(RFM95_SS_PIN);
}

void rfm95_write_fifo(const uint8_t *data, size_t len){
    gpio_clr(RFM95_SS_PIN);
    usart0_transfer_byte(RFM95_FIFO | 0x80);
    usart0_transfer(data, len);
    gpio_set(RFM95_SS_PIN);
}

void rfm95_read_memory(uint8_t addr, uint8_t *data, size_t len){
    rfm95_write_reg(RFM95_FIFO_ADDR, addr);
    rfm95_read_fifo(data, len);
}

void rfm95_write_memory(uint8_t addr, const uint8_t *data, size_t len){
    rfm95_write_reg(RFM95_FIFO_ADDR, addr);
    rfm95_write_fifo(data, len);
}

void rfm95_set_freq(uint32_t freq_hz){
    uint64_t frf = ((uint64_t)(freq_hz) << 17) / 32000000ULL;
    rfm95_write_reg(RFM95_FRF_MSB, (frf >> 16) & 0xff);
    rfm95_write_reg(RFM95_FRF_MID, (frf >> 8) & 0xff);
    rfm95_write_reg(RFM95_FRF_LSB, (frf >> 0) & 0xff);
}

void rfm95_dump_regs() {
    unsigned int i;
    uint8_t memory[256];
    leuart0_printf("RFM95 Regs:\n");
    for(i = 0; i < 0x80; i++){
        leuart0_printf(" %hhx", rfm95_read_reg(i));
        if((i & 0x0f) == 0x0f) leuart0_printf("\n");
    }
    leuart0_printf("RFM95 Memory:\n");
    rfm95_read_memory(0x00, memory, sizeof(memory));
    for(i = 0; i < sizeof(memory); i++){
        leuart0_printf(" %hhx", memory[i]);
        if((i & 0x0f) == 0xf) leuart0_printf("\n");
    }
}

void set_field(uint8_t reg, uint8_t mask, uint8_t value) {
    rfm95_write_reg(reg, (rfm95_read_reg(reg) & ~mask) | value);
}

uint8_t rfm95_mode_get() {
    return rfm95_read_reg(RFM95_OPMODE) & RFM95_OPMODE_MODE_MASK;
}

void rfm95_mode_set(uint8_t mode) {
    set_field(RFM95_OPMODE, RFM95_OPMODE_MODE_MASK, mode);
}

void rfm95_wait_tx() {
    if (rfm95_mode_get() == RFM95_OPMODE_TX)
        while(rfm95_read_reg(RFM95_IRQ) & RFM95_IRQ_TX_DONE);
}

void rfm95_send(const uint8_t* data, uint8_t len) {

    // wait for transmission of old packet

    rfm95_wait_tx();
    rfm95_mode_set(RFM95_OPMODE_STANDBY);

    // write packet

    rfm95_write_memory(0, data, len);
    rfm95_write_reg(RFM95_PAYLOAD_LENGTH, len);

    // transmit new packet

    rfm95_mode_set(RFM95_OPMODE_TX);
}

int rfm95_packet_available() {

    uint8_t irq = rfm95_read_reg(RFM95_IRQ);
    uint8_t len = 0;

    // TODO: try-hard, be good

    switch(rfm95_mode_get()) {
        case RFM95_OPMODE_RX:
            if (irq & RFM95_IRQ_RX_DONE) {
                len  = rfm95_read_reg(RFM95_RX_BYTES);
                rfm95_write_reg(
                    RFM95_FIFO_ADDR,
                    0
                );
            }
            break;

        case RFM95_OPMODE_CAD:
            // TODO: more stuff here
            break;
    }

    return len;
}

uint8_t rfm95_recv(uint8_t* buf, uint8_t max_len) {

    rfm95_mode_set(RFM95_OPMODE_RX);

    while(!rfm95_packet_available());

    return 0;
}

void rfm95_init(){
    gpio_mode(RFM95_SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_mode(RFM95_RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_clr(RFM95_RST_PIN);
    delay(5);
    gpio_set(RFM95_RST_PIN);
    delay(5);

    // enter LoRa mode

    rfm95_mode_set(RFM95_OPMODE_SLEEP);

    while(rfm95_mode_get() != RFM95_OPMODE_SLEEP);

    set_field(
        RFM95_OPMODE,
        RFM95_OPMODE_LONG_RANGE_MODE_MASK,
        RFM95_OPMODE_LORA);

    // use entire FIFO for rx & tx

    rfm95_write_reg(RFM95_RXBASE, 0);
    rfm95_write_reg(RFM95_TXBASE, 0);

    // set preample size : default = 8

    rfm95_mode_set(RFM95_OPMODE_STANDBY);
    rfm95_write_reg(RFM95_PREAMBLE_MSB, 0);
    rfm95_write_reg(RFM95_PREAMBLE_LSB, 8);

    // set frequency

    rfm95_set_freq(868000000);

    uint32_t cnt = 0;

    while(1) {
        // rfm95_recv(NULL, 0);
        uint32_t v = cnt;
        rfm95_send(&v, sizeof(v));
        cnt++;
        delay(1000);
        rfm95_dump_regs();
    }
}
