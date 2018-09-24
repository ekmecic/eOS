#pragma once

#include "core/types.h"

#include "core/task.h"
#include "startup/startup.h"

// Defined in linker file
extern u32 __stack_end;

void systick_handler(void) {
  eos_printf("systick fired\n");
  // Trigger a PendSV interrupt
  *((uint32_t volatile*)0xE000ED04) = 0x10000000;
}

void fault_handler(void) {
  // Read {usage, bus, memory management} fault status registers
  __attribute__((unused)) volatile u16 ufsr  = *((u16*)0xE000ED2A);
  __attribute__((unused)) volatile u8  bfsr  = *((u8*)0xE000ED29);
  __attribute__((unused)) volatile u8  mmfsr = *((u8*)0xE000ED28);

  // Set a breakpoint
  __asm__ volatile("bkpt #0");
}

__attribute__((section(".stack_top"), used)) u32* st = &__stack_end;

__attribute__((section(".vectors"), used)) void (*vector_table[])(void) = {
    // Core system interrupts
    eos_startup,     // isr_reset,
    0,               // isr_nmi,
    fault_handler,   // isr_hard_fault,
    fault_handler,   // isr_mem_manage_fault,
    fault_handler,   // isr_bus_fault,
    fault_handler,   // isr_usage_fault,
    0,               // isr_reserved1,
    0,               // isr_reserved2,
    0,               // isr_reserved3,
    0,               // isr_reserved4,
    0,               // isr_svc,
    0,               // isr_debug_monitor,
    0,               // isr_reserved5,
    pendsv_handler,  // isr_pendsv,
    systick_handler, // isr_systick,

    // Other interrupts
    0, // isr_wwdg,
    0, // isr_pvd,
    0, // isr_tamper_stamp,
    0, // isr_rtc_wkup,
    0, // isr_flash,
    0, // isr_rcc,
    0, // isr_exti0,
    0, // isr_exti1,
    0, // isr_exti2_ts,
    0, // isr_exti3,
    0, // isr_exti4,
    0, // isr_dma1_ch1,
    0, // isr_dma1_ch2,
    0, // isr_dma1_ch3,
    0, // isr_dma1_ch4,
    0, // isr_dma1_ch5,
    0, // isr_dma1_ch6,
    0, // isr_dma1_ch7,
    0, // isr_adc1_2,
    0, // isr_usb_hp_can_tx,
    0, // isr_usb_lp_can_rx0,
    0, // isr_can_rx1,
    0, // isr_can_sce,
    0, // isr_exti9_5,
    0, // isr_tim1_brk_tim15,
    0, // isr_tim1_up_tim16,
    0, // isr_tim1_trg_com_tim17,
    0, // isr_tim1_cc,
    0, // isr_tim2,
    0, // isr_tim3,
    0, // isr_tim4,
    0, // isr_i2c1_ev,
    0, // isr_i2c_er,
    0, // isr_i2c2_ev,
    0, // isr_i2c2_er,
    0, // isr_spi1,
    0, // isr_spi2,
    0, // isr_usart1,
    0, // isr_usart2,
    0, // isr_usart3,
    0, // isr_exti15_10,
    0, // isr_rtc_alarm,
    0, // isr_usb_wakeup,
    0, // isr_tim8_brk,
    0, // isr_tim8_up,
    0, // isr_tim8_trg_com,
    0, // isr_tim8_cc,
    0, // isr_adc3,
    0, // isr_fmc,
    0, // isr_spi3,
    0, // isr_uart4,
    0, // isr_uart5,
    0, // isr_tim6_dac,
    0, // isr_tim7,
    0, // isr_dma2_ch1,
    0, // isr_dma2_ch2,
    0, // isr_dma2_ch3,
    0, // isr_dma2_ch4,
    0, // isr_dma2_ch5,
    0, // isr_adc4,
    0, // isr_comp1_2_3,
    0, // isr_comp4_5_6,
    0, // isr_comp7,
    0, // isr_i2c3_ev,
    0, // isr_i2c3_er,
    0, // isr_usb_hp,
    0, // isr_usb_lp,
    0, // isr_usb_wakeup_rmp,
    0, // isr_tim20_brk,
    0, // isr_tim20_up,
    0, // isr_tim20_trg_com,
    0, // isr_fpu
};
