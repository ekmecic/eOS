#include "core/types.h"

#include "mem.h"

void memset(u32 *start, u32 pattern, u32 len) {
  while (len) {
    *start = pattern;
    start++;
    len--;
  }
}

void memcpy(u32 *src, u32 *dest, u32 len) {
  while (len) {
    *dest = *src;
    src++;
    dest++;
    len--;
  }
}
