#include "mcu.h"
#include "rtc.h"
#include "util.h"

void RTC_Handler(void){
    // Clear interrupt flag
    RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;

    // increment ticks
    ms_ticks++;
}

void init_rtc(void){
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
