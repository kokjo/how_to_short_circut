#include <stdint.h>
#include <stdbool.h>

#include "em_device.h"
#include "toboot-api.h"
#include "gpio.h"
#include "leuart.h"

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
    while(ms_ticks - start < ms) asm("wfi");
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
    CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_LE;

    // Enable peripheral clocks(21MHz / 4, enable GPIO and ADC0).
    CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN | CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK4;
    CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO | CMU_HFPERCLKEN0_ADC0;

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

void main(){
    int pe13_voltage = 0;
    init_clocks();
    gpio_mode(GREEN, GPIO_MODE_WIREDAND);
    gpio_set(GREEN);
    init_leuart0();
    init_rtc();
    
    while(1){
        pe13_voltage = adc_sample_ch1();
        // Toggle Green LED
        gpio_tgl(GREEN);
        
        // print some output 
        leuart0_printf("ADC CH1: 0x%x\n", pe13_voltage);
    
        delay(pe13_voltage >> 2);
    }
}
