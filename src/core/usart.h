#pragma once
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

void eos_usart_print(char *);
void eos_usart_println(char *);
void eos_usart_init();
