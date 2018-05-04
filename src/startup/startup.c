#include "core/types.h"

#include "core/mem.h"
#include "core/systick.h"
#include "core/usart.h"
#include "startup/interrupt_vector_table.h"
#include "startup/startup.h"

extern u32 __bss_begin, __bss_end;
extern u32 __data_begin, __data_end;
extern u32 __datai_begin, __datai_end;
extern u32 __stack_end;

extern void main(void);

void eos_startup(void) {
  // Copy the data segment
  memcpy(&__datai_begin, &__data_begin, &__datai_end - &__datai_begin);

  // Zero out flash
  memset(&__bss_begin, 0, &__bss_begin - &__bss_end);

  // Enable kernel USART
  eos_usart_init();

  // Enable systick interrupt
  /* eos_systick_init(); */

  // Run the main program
  main();
}
