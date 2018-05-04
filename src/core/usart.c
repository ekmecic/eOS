#include "usart.h"

void eos_usart_print(char *str) {
  char *c = str;
  while (*c != '\0') {
    usart_send_blocking(USART2, *c);
    c++;
  }
}

void eos_usart_println(char *str) {
  eos_usart_print(str);
  usart_send_blocking(USART2, '\n');
}

void eos_usart_init() {
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_USART2);
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_enable(USART2);
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}
