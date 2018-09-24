#include "core/types.h"

#include "config.h"
#include "core/task.h"
#include "core/util.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

void delay(u32 time) {
  for (u32 i = 0; i < time; i++)
    for (u8 j = 0; j < 255; j++)
      ;
}

void task1(void) {
  while (true) {
    eos_printf("Hello from task #1!\n");
    gpio_toggle(GPIOA, GPIO5);
    delay(10000);
  }
}

void main(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

  u32  task_stack[256];
  u32* task_stack_start = task_stack + 256 - 16;
  task_stack_start[8]   = (u32)&task1;

  eos_start_task(task_stack_start);
}
