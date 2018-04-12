#ifndef GPIO_H
#define GPIO_H
#include "mcu.h"

#define PA0  (0x00) 
#define PA1  (0x01)
#define PA2  (0x02)
#define PA3  (0x03)
#define PA4  (0x04)
#define PA5  (0x05)
#define PA6  (0x06)
#define PA7  (0x07)
#define PA8  (0x08)
#define PA9  (0x09)
#define PA10 (0x0a)
#define PA11 (0x0b)
#define PA12 (0x0c)
#define PA13 (0x0d)
#define PA14 (0x0e)
#define PA15 (0x0f)

#define PB0  (0x10)
#define PB1  (0x11)
#define PB2  (0x12)
#define PB3  (0x13)
#define PB4  (0x14)
#define PB5  (0x15)
#define PB6  (0x16)
#define PB7  (0x17)
#define PB8  (0x18)
#define PB9  (0x19)
#define PB10 (0x1a)
#define PB11 (0x1b)
#define PB12 (0x1c)
#define PB13 (0x1d)
#define PB14 (0x1e)
#define PB15 (0x1f)

#define PC0  (0x20)
#define PC1  (0x21)
#define PC2  (0x22)
#define PC3  (0x23)
#define PC4  (0x24)
#define PC5  (0x25)
#define PC6  (0x26)
#define PC7  (0x27)
#define PC8  (0x28)
#define PC9  (0x29)
#define PC10 (0x2a)
#define PC11 (0x2b)
#define PC12 (0x2c)
#define PC13 (0x2d)
#define PC14 (0x2e)
#define PC15 (0x2f)

#define PD0  (0x30)
#define PD1  (0x31)
#define PD2  (0x32)
#define PD3  (0x33)
#define PD4  (0x34)
#define PD5  (0x35)
#define PD6  (0x36)
#define PD7  (0x37)
#define PD8  (0x38)
#define PD9  (0x39)
#define PD10 (0x3a)
#define PD11 (0x3b)
#define PD12 (0x3c)
#define PD13 (0x3d)
#define PD14 (0x3e)
#define PD15 (0x3f)

#define PE0  (0x40)
#define PE1  (0x41)
#define PE2  (0x42)
#define PE3  (0x43)
#define PE4  (0x44)
#define PE5  (0x45)
#define PE6  (0x46)
#define PE7  (0x47)
#define PE8  (0x48)
#define PE9  (0x49)
#define PE10 (0x4a)
#define PE11 (0x4b)
#define PE12 (0x4c)
#define PE13 (0x4d)
#define PE14 (0x4e)
#define PE15 (0x4f)

#define PF0  (0x50)
#define PF1  (0x51)
#define PF2  (0x52)
#define PF3  (0x53)
#define PF4  (0x54)
#define PF5  (0x55)
#define PF6  (0x56)
#define PF7  (0x57)
#define PF8  (0x58)
#define PF9  (0x59)
#define PF10 (0x5a)
#define PF11 (0x5b)
#define PF12 (0x5c)
#define PF13 (0x5d)
#define PF14 (0x5e)
#define PF15 (0x5f)

#define GPIO_BANK(pin) (((pin) >> 4) & 0xf)
#define GPIO_IDX(pin) ((pin) & 0xf)

#define GPIO_MODE_DISABLED 0
#define GPIO_MODE_INPUT 1
#define GPIO_MODE_INPUTPULL 2
#define GPIO_MODE_INPUTPULLFILTER 3
#define GPIO_MODE_PUSHPULL 4
#define GPIO_MODE_PUSHPULLDRIVE 5
#define GPIO_MODE_WIREDOR 6
#define GPIO_MODE_WIREDORPULLDOWN 7
#define GPIO_MODE_WIREDAND 8
#define GPIO_MODE_WIREDANDFILTER 9
#define GPIO_MODE_WIREDANDPULLUP 10
#define GPIO_MODE_WIREDANDPULLUPFILTER 11
#define GPIO_MODE_WIREDANDDRIVE 12
#define GPIO_MODE_WIREDANDDRIVEFILTER 13
#define GPIO_MODE_WIREDANDDRIVEPULLUP 14
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER 15

void gpio_clr(int pin);
void gpio_set(int pin);
void gpio_tgl(int pin);
void gpio_mode(int pin, int mode);

#endif
