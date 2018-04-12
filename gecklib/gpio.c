#include "mcu.h"
#include "gpio.h"

void gpio_clr(int pin){
    GPIO->P[GPIO_PORT(pin)].DOUTCLR = (1 << GPIO_NR(pin));
}

void gpio_set(int pin){
    GPIO->P[GPIO_PORT(pin)].DOUTSET = (1 << GPIO_NR(pin));
}

void gpio_tgl(int pin){
    GPIO->P[GPIO_PORT(pin)].DOUTTGL = (1 << GPIO_NR(pin));
}

void gpio_mode(int pin, int mode){
    int port = GPIO_PORT(pin);
    int nr = GPIO_NR(pin);
    volatile uint32_t *reg = &GPIO->P[port].MODEL;
    if(nr & 8) {
        nr -= 8;
        reg = &GPIO->P[port].MODEH;
    }
    *reg &= ~(15 << (4*nr));
    *reg |= (mode & 15) << (4*nr);
}

int gpio_input(int pin){
    return (GPIO->P[GPIO_PORT(pin)].DIN >> GPIO_NR(pin)) & 1;
}
