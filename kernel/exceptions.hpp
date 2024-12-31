#ifndef MOYAIOS_EXCEPTIONS_HPP_
#define MOYAIOS_EXCEPTIONS_HPP_

#include <stdint.h>

void kernel_panic(const char* msg);

void divide_by_zero_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void single_step_trap(uint32_t cs, uint32_t eip, uint32_t eflags);
void nmi_trap(uint32_t cs, uint32_t eip, uint32_t eflags);
void breakpoint_trap(uint32_t cs, uint32_t eip, uint32_t eflags);
void overflow_trap(uint32_t cs, uint32_t eip, uint32_t eflags);
void bounds_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void invalid_opcode_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void no_device_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void double_fault_abort(uint32_t cs, uint32_t eip, uint32_t eflags);
void invalid_tss_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void no_segment_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void stack_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void general_protection_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void page_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void alignment_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags);
void machind_check_report(uint32_t cs, uint32_t eip, uint32_t eflags);
void simd_fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

void exceptions_init();

// for debugging purposes
void trigger_divide_by_zero();

#endif
