#pragma once

#include "core/types.h"

void eos_disable_isr(void);
void eos_enable_isr(void);
void eos_task_init(void (*func)(void), u32* stack, u32 stack_size);

void* get_msp(void);
void* get_psp(void);
void  set_msp(u32* new_stack_pointer);
void  set_psp(u32* new_stack_pointer);

void save_context(void);
void load_context(u32* psp);

void sys_isb(void);
void set_control(u32 val);

typedef struct {
  u32* psp;           // process stack pointer
  void (*func)(void); // function
} eos_task;
