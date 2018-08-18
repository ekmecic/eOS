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

static u32 p1_stack[EOS_DEFAULT_STACK_SIZE];

void fast_led_blinker(void) {
  while (true) {
    gpio_toggle(GPIOA, GPIO5);
    delay(10000);
  }
}

void main(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

  eos_task_init(fast_led_blinker, p1_stack, EOS_DEFAULT_STACK_SIZE);

  while (true) {
    eos_printf("test: %x, %d\n", 4096, 4096);
    gpio_toggle(GPIOA, GPIO5);
    delay(30000);
  }
}
