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

void rfm95_write_fifo(uint8_t *data, size_t len){
    gpio_clr(RFM95_SS_PIN); 
    usart0_transfer_byte(RFM95_FIFO | 0x80);
    usart0_transfer(data, len);
    gpio_set(RFM95_SS_PIN);
}

void rfm95_read_memory(uint8_t addr, uint8_t *data, size_t len){
    rfm95_write_reg(RFM95_FIFO_ADDR, addr);
    rfm95_read_fifo(data, len);
}

void rfm95_write_memory(uint8_t addr, uint8_t *data, size_t len){
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

void rfm95_init(){
    gpio_mode(RFM95_SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_mode(RFM95_RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_clr(RFM95_RST_PIN);
    delay(5);
    gpio_set(RFM95_RST_PIN);
    delay(5);
}
