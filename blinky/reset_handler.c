#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "toboot-api.h"

// Configure Toboot by identifying this as a V2 header.
// Place the header at page 16, to maintain compatibility with
// the serial bootloader and legacy programs.
__attribute__((used, section(".toboot_header"))) struct toboot_configuration toboot_configuration = {
    .magic = TOBOOT_V1_MAGIC,
    .start = 16,
    .config = TOBOOT_CONFIG_FLAG_ENABLE_IRQ,
};

__attribute__((section(".toboot_runtime"))) extern struct toboot_runtime toboot_runtime;

__attribute__ ((noreturn, weak)) void main(void) {
  while(1);
}

void Reset_Handler(void){
    // Reset the boot counter, to prevent boot loops
    toboot_runtime.boot_count = 0;

    // Disable the watchdog timer
    WDOG->CTRL = 0;

    main();
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
