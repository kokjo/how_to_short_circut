#include <stdint.h>
#include <stdbool.h>

#include "mcu.h"
#include "toboot-api.h"

typedef void  (*irq_vector_t)(void);

typedef struct {
    uint32_t *init_stack;
    irq_vector_t reset_handler;
    irq_vector_t nmi_handler;
    irq_vector_t hardfault_handler;
    irq_vector_t memmanage_handler;
    irq_vector_t busfault_handler;
    irq_vector_t usagefault_handler;
    irq_vector_t vector1c;
    irq_vector_t vector20;
    irq_vector_t vector24;
    irq_vector_t vector28;
    irq_vector_t svc_handler;
    irq_vector_t debugmonitor_handler;
    irq_vector_t vector34;
    irq_vector_t pendsv_handler;
    irq_vector_t systick_handler;
    irq_vector_t dma_handler;
    irq_vector_t gpio_even_handler;
    irq_vector_t timer0_handler;
    irq_vector_t acmp0_handler;
    irq_vector_t adc0_handler;
    irq_vector_t i2c0_handler;
    irq_vector_t gpio_odd_handler;
    irq_vector_t timer1_handler;
    irq_vector_t usart1_rx_handler;
    irq_vector_t usart1_tx_handler;
    irq_vector_t leuart0_handler;
    irq_vector_t pcnt0_handler;
    irq_vector_t rtc_handler;
    irq_vector_t cmu_handler;
    irq_vector_t vcmp_handler;
    irq_vector_t msc_handler;
    irq_vector_t aes_handler;
    irq_vector_t usart0_rx_handler;
    irq_vector_t usart0_tx_handler;
    irq_vector_t usb_handler;
    irq_vector_t timer2_handler;
} vectors_t;

void _unhandled_exception(void) {
    asm("bkpt #0");
    while(1) {}
}

extern uint32_t __stack;
void Reset_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void NMI_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void HardFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void MemManage_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void BusFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void UsageFault_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector1C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector20(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector24(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector28(void) __attribute__((weak, alias("_unhandled_exception")));
void SVC_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void DebugMon_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector34(void) __attribute__((weak, alias("_unhandled_exception")));
void PendSV_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void SysTick_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void RTC_Handler(void) __attribute__((weak, alias("_unhandled_exception")));
void LEUART0_Handler(void) __attribute__((weak, alias("_unhandled_exception")));

__attribute__ ((used, section(".vectors"))) vectors_t _vectors = {
    .init_stack = &__stack,
    .reset_handler = Reset_Handler,
    .nmi_handler = NMI_Handler,
    .hardfault_handler = HardFault_Handler,
    .memmanage_handler = MemManage_Handler,
    .busfault_handler = BusFault_Handler,
    .usagefault_handler = UsageFault_Handler,
    .vector1c = Vector1C,
    .vector20 = Vector20,
    .vector24 = Vector24,
    .vector28 = Vector28,
    .svc_handler = SVC_Handler,
    .debugmonitor_handler = DebugMon_Handler,
    .vector34 = Vector34,
    .pendsv_handler = PendSV_Handler,
    .systick_handler = SysTick_Handler,
    .rtc_handler = RTC_Handler,
    .leuart0_handler = LEUART0_Handler,
};
