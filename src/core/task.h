#pragma once
#include "core/types.h"

typedef struct {
  u32* psp;           // Process stack pointer
  void (*func)(void); // Task function pointer
  u8 priority;        // Task priority 0 (highest) to 255 (lowest)
} eos_task;

void eos_start_task(u32* psp);
void eos_create_task(u32* psp, void (*func)(void), const u32 stack_size, const u8 priority);
