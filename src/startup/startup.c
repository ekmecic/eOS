#include "config.h"
#include "core/types.h"

#include "core/mem.h"
#include "core/usart.h"
#include "core/util.h"
#include "startup/interrupt_vector_table.h"
#include "startup/startup.h"

#include <libopencm3/stm32/rcc.h>

extern u32 __bss_begin, __bss_end;
extern u32 __data_begin, __data_end;
extern u32 __datai_begin, __datai_end;
extern u32 __stack_end;

extern void main(void);

// Print current version and build info
void eos_print_version(void) {
  eos_printf("\n\neOS version " EOS_VERSION "\n"
             "Compiled on " __DATE__ " " __TIME__ "\n\n");
}

void eos_startup(void) {
  // Copy the data segment
  memcpy(&__datai_begin, &__data_begin, &__datai_end - &__datai_begin);

  // Zero out flash
  memset(&__bss_begin, 0, &__bss_end - &__bss_begin);

  // Set system clock to 64MHz based on the interal
  rcc_clock_setup_hsi(&rcc_hsi_8mhz[RCC_CLOCK_64MHZ]);

  // Enable kernel USART
  eos_usart_init();

  // Enable systick interrupt
  /* eos_systick_init(); */

  // Print the current version and run the main program
  eos_print_version();

  eos_printf(
      "bss_begin: %x\n"
      "bss_end: %x\n"
      "data_begin: %x\n"
      "data_end: %x\n"
      "datai_begin: %x\n"
      "datai_end: %x\n"
      "stack_end: %x\n",
      &__bss_begin,
      &__bss_end,
      &__data_begin,
      &__data_end,
      &__datai_begin,
      &__datai_end,
      &__stack_end);
  main();
}
