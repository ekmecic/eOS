#include "core/types.h"

#include "mem.h"

// Set len words to pattern, starting from start address
void memset(u32* start, u32 pattern, u32 len) {
  while (len) {
    *start = pattern;
    start++;
    len--;
  }
}

// Copy len words from src address to dest addr
void memcpy(u32* src, u32* dest, u32 len) {
  while (len) {
    *dest = *src;
    src++;
    dest++;
    len--;
  }
}
