#pragma once

//
// eOS version
//
#define EOS_VERSION "0.1.0"

//
// Kernel USART settings
//
#define EOS_USART USART2                    // USART for kernel serial output
#define EOS_USART_CLOCK RCC_USART2          // USART for kernel serial output
#define EOS_USART_BAUD_RATE 1000000         // USART baud rate (1Mb/s)
#define EOS_USART_DATABITS 8                // USART data bits
#define EOS_USART_STOPBITS USART_STOPBITS_1 // USART stop bits
#define EOS_USART_MODE USART_MODE_TX        // USART mode (tx, rx, tx/rx)
#define EOS_USART_PARITY USART_PARITY_NONE  // USART parity
#define EOS_USART_FLOW_CONTROL USART_FLOWCONTROL_NONE // USART flow control

//
// Kernel USART GPIO settings
//
#define EOS_USART_TX_GPIO_CLOCK RCC_GPIOA // TX GPIO port
#define EOS_USART_TX_GPIO_PORT GPIOA      // TX GPIO port
#define EOS_USART_TX_GPIO_PIN GPIO2       // TX GPIO pin number
#define EOS_USART_TX_GPIO_AF GPIO_AF7     // TX GPIO alternate function
