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

void task2(void) {
  while (true) {
    eos_printf("Task #2!\n");
  }
}

void main(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

  u32 task1_stack[256];
  eos_create_task(task1_stack, task1, EOS_DEFAULT_STACK_SIZE, 255);

  u32 task2_stack[256];
  eos_create_task(task2_stack, task2, EOS_DEFAULT_STACK_SIZE, 255);

  eos_start();

  while (1)
    ;
}
