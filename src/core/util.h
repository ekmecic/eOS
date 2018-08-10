#pragma once

#include "core/types.h"

#include <stdarg.h>

void eos_printf(const char* str, ...);
void eos_fprintf(const char* str, char* buf, va_list arg);
u8   eos_itoa(i32 num, char* buf, u8 radix);
