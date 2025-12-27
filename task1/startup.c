#include <stdint.h>

/* Symbols defined by the linker script */
extern uint32_t _estack;
extern uint32_t _sdata, _edata, _la_data;
extern uint32_t _sbss, _ebss;

void Reset_Handler(void);
extern int main(void);

/* FreeRTOS Interrupt Handlers (mapped in FreeRTOSConfig.h) */
extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

/* Interrupt Vector Table */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))(&_estack), /* 0: Initial Stack Pointer */
    Reset_Handler,               /* 1: Reset Handler */
    0, 0, 0, 0, 0, 0, 0, 0, 0,   /* 2-10: Reserved */
    SVC_Handler,                 /* 11: SVC Handler */
    0, 0,                        /* 12-13: Reserved */
    PendSV_Handler,              /* 14: PendSV Handler */
    SysTick_Handler              /* 15: SysTick Handler */
};

void Reset_Handler(void) {
    /* 1. Copy initialized data (.data) from Flash to RAM */
    uint32_t *src = &_la_data;
    uint32_t *dest = &_sdata;
    while (dest < &_edata) *dest++ = *src++;

    /* 2. Clear uninitialized data (.bss) to zero */
    dest = &_sbss;
    while (dest < &_ebss) *dest++ = 0;

    /* 3. Call the application entry point */
    main();

    /* Should never return */
    while(1);
}
