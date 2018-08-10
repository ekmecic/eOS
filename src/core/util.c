#include "util.h"
#include "core/usart.h"

#include <stdbool.h>

u8 eos_itoa(i32 num, char *buf, u8 radix) {
  const char itoa_lut[20] = "0123456789ABCDEF";

  // Fail for crazy radixes
  if (radix > 16) {
    buf[0] = '?';
    return 1;
  }

  // Check negativity for later use
  bool is_negative = false;
  if (num < 0 && radix == 10) {
    is_negative = true;
    num = 0 - num;
  }

  // Construct a backwards string using the lut
  u8 num_chars;
  for (num_chars = 0; num > 0; num_chars++) {
    buf[num_chars] = itoa_lut[num % radix];
    num /= radix; // remove the last digit of the number
  }

  // Insert the negative sign
  if (is_negative) {
    buf[num_chars++] = '-';
  }

  // Add '0x' to hex numbers
  if (radix == 16) {
    buf[num_chars++] = 'x';
    buf[num_chars++] = '0';
  }

  // Reverse the string while ignoring padding zeros
  for (u8 i = 0; i < (num_chars / 2); i++) {
    char tmp = buf[i];
    buf[i] = buf[num_chars - i - 1];
    buf[num_chars - i - 1] = tmp;
  }

  // Return the number of bytes taken up in the buffer
  return num_chars;
}

void eos_fprintf(const char *str, char *buf, va_list arg) {
  for (; *str != '\0'; str++) {
    // If we see a formatting specifier, jump ahead to the next char and
    // call itoa accordingly
    if (*str == '%') {
      str++; // go to next char after %
      switch (*str) {
      // Decimal
      case 'd': {
        buf += eos_itoa(va_arg(arg, i32), buf, 10);
        break;
      }
      // Hexadecimal
      case 'x':
        buf += eos_itoa(va_arg(arg, i32), buf, 16);
        break;
      // Gibberish
      default:
        break;
      }
    }
    // Normal character without a format specifier
    else {
      *buf++ = *str;
    }
  }
  *buf++ = '\0';
}

void eos_printf(const char *str, ...) {
  char eos_usart_buffer[256];
  va_list args;

  va_start(args, str);
  eos_fprintf(str, eos_usart_buffer, args);
  va_end(args);

  eos_usart_print(eos_usart_buffer);
}
