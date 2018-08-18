#include "task.h"
#include "config.h"
#include "core/util.h"

static struct {
  eos_task tasks[EOS_MAX_TASKS]; // array of all tasks
} eos_task_table;

static void task_end(void) {
  while (1)
    ;
}

void eos_task_init(void (*func)(void), u32* stack, u32 stack_size) {
  // set up the task struct
  eos_task* task = &eos_task_table.tasks[0];
  task->func     = func;
  task->psp      = stack + stack_size - 15;

  eos_printf("stack[stack_size] %x\n", &stack[stack_size]);
  eos_printf("stack[stack_size - 15] %x\n", &stack[stack_size - 15]);

  // set up the contents of the task so that load_context can work properly
  stack[stack_size]      = 0x01000000;     // xPSR:  default value
  stack[stack_size - 1]  = (u32)&task->func;     // PC
  stack[stack_size - 2]  = (u32)&task_end; // LR
  /* stack[stack_size - 3]  = 12;             // R12 */
  /* stack[stack_size - 4]  = 3;              // R3 */
  /* stack[stack_size - 5]  = 2;              // R2 */
  /* stack[stack_size - 6]  = 1;              // R1 */
  /* stack[stack_size - 7]  = 0;              // R0 */
  /* stack[stack_size - 8]  = 11;             // R11 */
  /* stack[stack_size - 9]  = 10;             // R10 */
  /* stack[stack_size - 10] = 9;              // R9 */
  /* stack[stack_size - 11] = 8;              // R8 */
  /* stack[stack_size - 12] = 7;              // R7 */
  /* stack[stack_size - 13] = 6;              // R6 */
  /* stack[stack_size - 14] = 5;              // R5 */
  /* stack[stack_size - 15] = 4;              // R4 */

  load_context(task->psp);
}

// Disable interrupts for critical sections
void eos_disable_isr(void) {
  __asm__ volatile("cpsid i");
}

// Enable interrupts after critical sections
void eos_enable_isr(void) {
  __asm__ volatile("cpsie i");
}

void* get_msp(void) {
  void* retval = 0;
  __asm__ volatile("mrs %[retval], msp" // move system register msp into retval
                   : [retval] "=r"(retval)
                   : // no inputs
                   : // no clobbers
  );
  return retval;
}

void* get_psp(void) {
  void* retval = 0;
  __asm__ volatile("mrs %[retval], psp"
                   : [retval] "=r"(retval)
                   : // no inputs
                   : // no clobbers
  );
  return retval;
}

void set_msp(u32* new_stack_pointer) {
  __asm__ volatile("msr msp, %[new_stack_pointer]"
                   : // no outputs
                   : [new_stack_pointer] "r"(new_stack_pointer)
                   : // no clobbers
  );
}

void set_psp(u32* new_stack_pointer) {
  __asm__ volatile(
      "isb\n\t"
      "msr psp, %[new_stack_pointer]\n\t"
      "isb\n\t"
      : // no outputs
      : [new_stack_pointer] "r"(new_stack_pointer)
      : "memory");
}

// Get the current process stack pointer
// Push registers r4 to r11 onto the stack
void save_context(void) {
  // Get the current process stack pointer
  u32* psp = (u32*)get_psp();
  __asm__ volatile(
      // Registers r4-r11 are not saved by the ARM hardware
      // so they must be pushed onto the current process stack
      // Note: "!" indicates that the psp will be incremented
      // by the size of the pushed data (8 * 4 = 32 bytes in this case)
      "stmdb %[psp]!, {r4-r11}"
      : [psp] "=r"(psp)
      : // no inputs
      : // no clobbers
  );
}

// Go to the given process stack
// Pop the saved r4-r11 registers from the stack into the CPU
// Set the process stack pointer to the new one (which resumes execution)
void load_context(u32* psp) {
  __asm__ volatile(
      // Load registers
      "ldmfd %[psp]!, {r4-r11}"
      : // no outputs
      : [psp] "r"(psp)
      : "memory");
  set_control(0x03);
  set_psp(psp);
}

void set_control(u32 val) {
  __asm__ volatile(
      "msr control, %[val]\n\t"
      "isb"
      : // no outputs
      : [val] "r"(val)
      : "memory");
}
