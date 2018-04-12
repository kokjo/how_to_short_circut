#ifndef __HEADER_UTIL__
#define __HEADER_UTIL__

#define RTC_INTERVAL_MSEC (1)
#define EFM32_LFRCO_FREQ  (32768UL)
#define EFM32_ULFRCO_FREQ (1000UL)

extern volatile int ms_ticks;

void delay(int ms);

#endif
