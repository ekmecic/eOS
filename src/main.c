#include "core/types.h"

#include "core/usart.h"
#include "core/util.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

void delay(u32 time) {
  for (u32 i = 0; i < time; i++)
    for (uint8_t j = 0; j < 255; j++)
      ;
}

void main(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

  while (true) {
    eos_printf("test: %x, %d\n", 4096, 4096);
    gpio_toggle(GPIOA, GPIO5);
    delay(30000);
  }
}
