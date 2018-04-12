#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "toboot-api.h"

#include "clocks.h"
#include "watchdog.h"
#include "util.h"
#include "rtc.h"

// Configure Toboot by identifying this as a V2 header.
// Place the header at page 16, to maintain compatibility with
// the serial bootloader and legacy programs.
__attribute__((used, section(".toboot_header"))) struct toboot_configuration toboot_configuration = {
    .magic = TOBOOT_V1_MAGIC,
    .start = 16,
    .config = TOBOOT_CONFIG_FLAG_ENABLE_IRQ,
};

__attribute__((section(".toboot_runtime"))) extern struct toboot_runtime toboot_runtime;

__attribute__ ((weak)) void main(void) {}
__attribute__ ((weak)) void init_early(void) {}

void Reset_Handler(void){

    ms_ticks = 0;

    // reset the boot counter, to prevent boot loops

    toboot_runtime.boot_count = 0;

    init_early();
    init_watchdog();
    init_clocks();
    init_rtc();

#ifdef ENABLE_LEUART0
    init_leuart0();
#endif

#ifdef ENABLE_USART0
    init_usart0();
#endif

    main();
    while(1);
}

/*
void NMI_Handler(void){
    asm("bkpt #1");
    while(1){};
}

void HardFault_Handler(void){
    asm("bkpt #2");
    while(1){};
}
*/
