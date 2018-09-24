#include "task.h"

#include "config.h"

static eos_task eos_task_table[EOS_MAX_TASKS];
static u32      eos_task_table_size = 0;

__attribute((naked)) void eos_start_task(u32* psp) {
  __asm__ volatile(
      // Save the kernel registers onto the kernel stack
      "push {r4-r11, ip, lr} \n\t"

      // Load values from the new process stack pointer into the CPU
      "ldmia %[psp]!, {r4-r11, lr} \n\t"
      "msr psp, %[psp] \n\t"

      // Start executing the user task
      "bx lr"
      : // no outputs
      : [psp] "r"(psp)
      : "memory");
}

void eos_create_task(u32* psp, void (*func)(void), const u32 stack_size, const u8 priority) {
  // Fill out an entry in the task table for the new task
  eos_task_table[eos_task_table_size].psp      = psp;
  eos_task_table[eos_task_table_size].func     = func;
  eos_task_table[eos_task_table_size].priority = priority;
  eos_task_table_size++;

  // Set up the task's stack
  psp += stack_size - 16;
  psp[8] = (u32)func;

  // Context switch to the new task
  eos_start_task(psp);
}
