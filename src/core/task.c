#include "task.h"

#include "config.h"

static eos_task eos_task_table[EOS_MAX_TASKS];
static u32      eos_task_table_size = 0;

void eos_create_task(u32* psp, void (*func)(void), const u32 stack_size, const u8 priority) {
  // Set up the task's stack and set
  psp += stack_size - 16;
  psp[8] = (u32)func;

  // Fill out an entry in the task table for the new task
  eos_task_table[eos_task_table_size].psp      = psp;
  eos_task_table[eos_task_table_size].func     = func;
  eos_task_table[eos_task_table_size].priority = priority;
  eos_task_table_size++;
}

// Starts OS process management and begins executing the first task
__attribute((naked)) void eos_start(void) {
  // Hardcoded values, to be replaced with scheduling in next commit
  u32* new_psp = eos_task_table[1].psp;
  __asm__ volatile(
      // Save the kernel registers onto the kernel stack
      "push {r4-r11, lr} \n\t"

      // Load values from the new process stack pointer into the CPU
      "mov r0, %[psp] \n\t"
      "ldmia r0!, {r4-r11, lr} \n\t"
      "msr psp, r0 \n\t"

      // Start executing the task
      "bx lr"
      : // no outputs
      : [psp] "r"(new_psp)
      : "memory");
}

// Switches context between tasks
__attribute((naked)) void pendsv_handler(void) {
  // Hardcoded values, to be replaced with scheduling in next commit
  u32* old_psp;
  u32* new_psp = eos_task_table[0].psp;

  __asm__ volatile(
      // Read out the old value of the PSP
      "mrs %[old_psp], psp \n\t"
      "mrs r0, psp \n\t"

      // Save the old context onto the old process stack
      "stmdb r0!, {r4-r11, lr} \n\t"

      // Read the new PSP value into R0
      // Can't directly use %[new_psp] in the ldmia instruction, so R0 is used
      "mov r0, %[new_psp] \n\t"
      "ldmia r0!, {r4-r11, lr} \n\t"

      // Set the PSP to the new stack pointer value
      "msr psp, r0 \n\t"

      // Execute the handler function of the new task
      "bx lr"
      : [old_psp] "=r"(old_psp)
      : [new_psp] "r"(new_psp)
      : "memory");
}
