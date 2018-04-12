#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "toboot-api.h"
#include "gpio.h"

#define RTC_INTERVAL_MSEC 1000

#define GREEN PB7
#define RED PA0

void RTC_Handler(void){
    // Clear interrupt flag
    RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;
   
    // Toggle Green LED
    gpio_tgl(GREEN);
}

void init_clocks(void){
    // Enable peripheral clocks.
    CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
    CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO;
    CMU->HFPERCLKDIV = 1 << 8;

    // Set the main CPU clock to run from USB
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFC_MASK) | CMU_LFCLKSEL_LFC_LFRCO;
    CMU->LFCCLKEN0 |= CMU_LFCCLKEN0_USBLE;

    // Calibrate USB based on communications
    CMU->USHFRCOCONF = CMU_USHFRCOCONF_BAND_48MHZ;

    // Enable USHFRCO Clock Recovery mode.
    CMU->USBCRCTRL |= CMU_USBCRCTRL_EN;

    /* Set HFRCO freq 21 MHz */
    CMU->HFRCOCTRL = (4 << 8) | (DEVINFO->HFRCOCAL1 & 0xff << 0);
    CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_LE;

    CMU->OSCENCMD = CMU_OSCENCMD_HFRCOEN;
    while (!(CMU->STATUS & CMU_STATUS_HFRCORDY)){}

    CMU->CMD |= CMU_CMD_HFCLKSEL_HFRCO;
    while ((CMU->STATUS & CMU_STATUS_HFRCOSEL) == 0){}
}

static void init_rtc(void){
    // Enable LFRCO for RTC
    CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
    // Enable RTC
    CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;

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
    init_clocks();
    gpio_mode(GREEN, GPIO_MODE_WIREDAND);
    gpio_set(GREEN);
    init_rtc();
    
    while(1) asm ("wfi");
}
