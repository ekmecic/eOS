#include "task.h"

__attribute((naked)) void eos_start_task(u32* psp) {
  __asm__ volatile(
      // Save the kernel registers onto the kernel stack
      "push {r4-r11, ip, lr} \n\t"

      // Move r0 (which holds new_stack_ptr, per ARM calling convention) into the PSP
      "ldmia %[psp]!, {r4-r11, lr} \n\t"
      "msr psp, %[psp] \n\t"

      // Start executing the user task
      "bx lr"
      : // no outputs
      : [psp] "r"(psp)
      : "memory");
}
