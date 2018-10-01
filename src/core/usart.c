#include "usart.h"

#include "config.h"
#include "core/types.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

// Print a string char-by-char to USART
void eos_usart_print(char* str) {
  for (u16 i = 0; str[i] != '\0'; i++) {
    usart_send_blocking(USART2, str[i]);
  }
}

// Initialize the kernel serial output clock, USART peripheral, and GPIO pins
void eos_usart_init() {
  // Enable kernel USART GPIO and peripheral clock
  rcc_periph_clock_enable(EOS_USART_TX_GPIO_CLOCK);
  rcc_periph_clock_enable(EOS_USART_CLOCK);

  // Configure parameters and enable kernel USART
  usart_set_baudrate(EOS_USART, EOS_USART_BAUD_RATE);
  usart_set_databits(EOS_USART, EOS_USART_DATABITS);
  usart_set_stopbits(EOS_USART, EOS_USART_STOPBITS);
  usart_set_mode(EOS_USART, USART_MODE_TX);
  usart_set_parity(EOS_USART, EOS_USART_PARITY);
  usart_set_flow_control(EOS_USART, EOS_USART_FLOW_CONTROL);
  usart_enable(EOS_USART);

  // Configure EOS USART TX line GPIO pin
  gpio_mode_setup(EOS_USART_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, EOS_USART_TX_GPIO_PIN);
  gpio_set_af(EOS_USART_TX_GPIO_PORT, EOS_USART_TX_GPIO_AF, EOS_USART_TX_GPIO_PIN);
}
