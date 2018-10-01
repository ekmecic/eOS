#include "systick.h"

#include <libopencm3/cm3/systick.h>

// Enable the systick interrupt at 1000Hz
void eos_systick_init(void) {
  // Enable the systick interrupt
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);

  // 9000000/9000 = 1000 overflows per second - every 1ms one interrupt
  // SysTick interrupt every N clock pulses: set reload to N-1
  systick_set_reload(8999);

  // Enable systick interrupt and start counting
  systick_interrupt_enable();
  systick_counter_enable();
}
