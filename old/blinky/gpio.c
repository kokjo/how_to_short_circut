#include "mcu.h"
#include "gpio.h"

void gpio_clr(int pin){
    GPIO->P[GPIO_BANK(pin)].DOUTCLR = (1 << GPIO_IDX(pin));
}

void gpio_set(int pin){
    GPIO->P[GPIO_BANK(pin)].DOUTSET = (1 << GPIO_IDX(pin));
}

void gpio_tgl(int pin){
    GPIO->P[GPIO_BANK(pin)].DOUTTGL = (1 << GPIO_IDX(pin));
}

int gpio_input(int pin){
    return (GPIO->P[GPIO_BANK(pin)].DIN >> GPIO_IDX(pin)) & 1;
}

void gpio_mode(int pin, int mode){
    int b = GPIO_BANK(pin);
    int i = GPIO_IDX(pin);
    if(i < 8) {
        GPIO->P[b].MODEL &= ~(15 << (i*4));
        GPIO->P[b].MODEL |= (mode & 15) << (i*4);
    } else {
        i -= 8;
        GPIO->P[b].MODEH &= ~(15 << (i*4));
        GPIO->P[b].MODEH |= (mode & 15) << (i*4);
    }
}
