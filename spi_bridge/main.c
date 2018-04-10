#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"

#include "em_device.h"
#include "toboot-api.h"
#include "gpio.h"
#include "leuart.h"
#include "usart.h"

#define RTC_INTERVAL_MSEC (1)
#define EFM32_LFRCO_FREQ  (32768UL)
#define EFM32_ULFRCO_FREQ (1000UL)

#define GREEN PB7
#define RED PA0

volatile int ms_ticks = 0;

void RTC_Handler(void){
    // Clear interrupt flag
    RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;

    // increment ticks
    ms_ticks++;
}

void delay(int ms){
    int start = ms_ticks;
    while(ms_ticks - start < ms);
}

void init_clocks(void){
    // Start LF 32768Hz RC oscillator
    CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
    while(!(CMU->STATUS & CMU_STATUS_LFRCORDY)){ } // WAIT

    // Start HF 21MHZ RC oscillator
    CMU->OSCENCMD = CMU_OSCENCMD_HFRCOEN;
    while(!(CMU->STATUS & CMU_STATUS_HFRCORDY)){ } // WAIT

    // Set HFRCO freq 21 MHz, and use calibration
    CMU->HFRCOCTRL = (4 << 8) | (DEVINFO->HFRCOCAL1 & 0xff << 0);

    // Set core clock to 21MHz / 2
    CMU->HFCORECLKDIV = CMU_HFCORECLKDIV_HFCORECLKLEDIV_DIV4;

    // Enable peripheral clocks(21MHz / 4, enable GPIO and ADC0).
    CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN | CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK512;
    CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO | CMU_HFPERCLKEN0_ADC0 | CMU_HFPERCLKEN0_USART0;

    // Enable RTC
    CMU->LFCLKSEL &= ~_CMU_LFCLKSEL_LFA_MASK;
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFA_LFRCO;
    CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;

    // Enable LEUART0
    CMU->LFCLKSEL &= ~_CMU_LFCLKSEL_LFB_MASK;
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFB_LFRCO;
    CMU->LFBCLKEN0 = CMU_LFBCLKEN0_LEUART0;
}

static void init_rtc(void){

    // Clear interrupt flags
    RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;
    // 250 ms wakeup time
    RTC->COMP0 = (RTC_INTERVAL_MSEC * EFM32_LFRCO_FREQ) / 1000;
    // Enable Interrupts on COMP0
    RTC->IEN = RTC_IEN_COMP0;
    // Enable RTC interrupts
    NVIC_EnableIRQ(RTC_IRQn);
    // Enable RTC
    RTC->CTRL = RTC_CTRL_COMP0TOP | RTC_CTRL_DEBUGRUN | RTC_CTRL_EN;
}

#define SS_PIN  (PB11)
#define RST_PIN (PB14)

void main(){
    char ch;
    int num = 0;
    uint8_t data = 0;
    
    init_clocks();
    init_leuart0();
    init_rtc();
    usart0_init();

    gpio_mode(SS_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(SS_PIN);
    gpio_mode(RST_PIN, GPIO_MODE_PUSHPULL);
    gpio_set(RST_PIN);

    delay(1000); 
    leuart0_printf("EFM32HG309 SPI LEUART BRIDGE\n");

    while(1){
        ch = leuart0_getchar();
        switch(ch){
            case '?':
                leuart0_printf("EFM32HG309 SPI LEUART BRIDGE\n");
                num = 0;
                data = 0;
                break;
            case '/':  gpio_set(SS_PIN);  break;
            case '\\': gpio_clr(SS_PIN);  break;
            case 'R':  gpio_set(RST_PIN); break;
            case 'r':  gpio_clr(RST_PIN); break;
            default:
                if('0' <= ch && ch <= '9'){
                    data = (data << 4) | ((ch - '0') + 0x0);
                    num++;
                }
                if('a' <= ch && ch <= 'f'){
                    data = (data << 4) | ((ch - 'a') + 0xa);
                    num++;
                }
                if('A' <= ch && ch <= 'F'){
                    data = (data << 4) | ((ch - 'A') + 0xa);
                    num++;
                }
                if(num == 2){
                    data = usart0_transfer_byte(data);
                    num = 0;
                    leuart0_printf("%hhx",data);
                }
        }
    }
}
