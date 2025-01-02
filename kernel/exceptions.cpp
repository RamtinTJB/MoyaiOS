#include "exceptions.hpp"
#include <debug.hpp>
#include "hw_interface.hpp"

void kernel_panic(const char* msg) {
  debug_printf("*[Kernel Panic]* : %s\n", msg);
}

void divide_by_zero_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Divide by 0");
  for (;;);
}

void single_step_trap(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Single Step");
  for (;;);
}

void nmi_trap(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("NMI trap");
  for (;;);
}

void breakpoint_trap(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Breakpoint trap");
  for (;;);
}

void overflow_trap(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Overflow trap");
  for (;;);
}

void bounds_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Bounds check fault");
  for (;;);
}

void invalid_opcode_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Invalid opcode fault");
  for (;;);
}

void no_device_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("No device fault");
  for (;;);
}

void double_fault_abort(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Double fault abort");
  for (;;);
}

void invalid_tss_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Invalid TSS fault");
  for (;;);
}

void no_segment_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("No segment fault");
  for (;;);
}

void stack_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Stack fault");
  for (;;);
}

void general_protection_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("General protection fault");
  for (;;);
}

void page_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Page fault");
  for (;;);
}

void fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("FPU fault");
  for (;;);
}

void alignment_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Alignment check fault");
  for (;;);
}

void machind_check_report(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Machine check report");
  for (;;);
}

void simd_fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("SIMD FPU fault");
  for (;;);
}

void exceptions_init() {
  set_int_vect(0, (I86_IRQ_HANDLER)divide_by_zero_fault);
  set_int_vect(1, (I86_IRQ_HANDLER)single_step_trap);
  set_int_vect(2, (I86_IRQ_HANDLER)nmi_trap);
  set_int_vect(3, (I86_IRQ_HANDLER)breakpoint_trap);
  set_int_vect(4, (I86_IRQ_HANDLER)overflow_trap);
  set_int_vect(5, (I86_IRQ_HANDLER)bounds_check_fault);
  set_int_vect(6, (I86_IRQ_HANDLER)invalid_opcode_fault);
  set_int_vect(7, (I86_IRQ_HANDLER)no_device_fault);
  set_int_vect(8, (I86_IRQ_HANDLER)double_fault_abort);
  set_int_vect(10, (I86_IRQ_HANDLER)invalid_tss_fault);
  set_int_vect(11, (I86_IRQ_HANDLER)no_segment_fault);
  set_int_vect(12, (I86_IRQ_HANDLER)stack_fault);
  set_int_vect(13, (I86_IRQ_HANDLER)general_protection_fault);
  set_int_vect(14, (I86_IRQ_HANDLER)page_fault);
  set_int_vect(16, (I86_IRQ_HANDLER)fpu_fault);
  set_int_vect(17, (I86_IRQ_HANDLER)alignment_check_fault);
  set_int_vect(18, (I86_IRQ_HANDLER)machind_check_report);
  set_int_vect(19, (I86_IRQ_HANDLER)simd_fpu_fault);
}

void trigger_divide_by_zero() {
  volatile int zero = 0;
  volatile int one = 1;
  int result = one/zero;
  (void)result;
}
