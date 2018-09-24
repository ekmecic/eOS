#include "task.h"

__attribute((naked)) void eos_start_task(__attribute__((unused)) u32* new_stack_ptr) {
  __asm__ volatile(
      // Save the kernel registers onto the kernel stack
      "push {r4-r11, ip, lr} \n\t"

      // Move r0 (which holds new_stack_ptr, per ARM calling convention) into the PSP
      "ldmia r0!, {r4-r11, lr} \n\t"
      "msr psp, r0 \n\t"

      // Start executing the user task
      "bx lr");
}
