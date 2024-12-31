#ifndef MOYAIOS_EXCEPTIONS_HPP_
#define MOYAIOS_EXCEPTIONS_HPP_

#include <stdint.h>

void kernel_panic(const char* msg);

/*
* Triggered when a division by zero is attempted or the 
* result of the division is too large to be represented.
*/
void divide_by_zero_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered during single-stepping for debugging purposes.
*/
void single_step_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered by a non-maskable interrupt, often used for critical
* hardware events such as memory parity errors.
*/
void nmi_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered by the INT 3 instruction, commonly used by debuggers to set breakpoints
*/
void breakpoint_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered by the INTO instruction when the overflow flag is set
*/
void overflow_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered by the BOUND instruction when the index is out of bounds
*/
void bounds_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when an invalid or undefined instruction is executed
*/
void invalid_opcode_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when a floating-point or SIMD instruction is executed without the coprocessor
*/
void no_device_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when a second exceptoin occurs while the CPU is attempting to handle an exception
*/
void double_fault_abort(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when a Task State Segment is invalid or inaccesible during
* a task switch
*/
void invalid_tss_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when a segment selector refers to an unavailable or non-present segment
*/
void no_segment_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered when a stack-segment fault occurs
*/
void stack_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/*
* Triggered by various protection violations, such as accessing restricted memory
*/
void general_protection_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/**
 * Triggered when an invalid page is accessed
 */
void page_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/**
 * Triggered by errors in floating-point operations
 */
void fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/**
 * Triggered when data misalignment is detected in memory accesses
 */
void alignment_check_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

/**
 * Triggered by hardware errors, such as memory corruption or CPU faults
 */
void machind_check_report(uint32_t cs, uint32_t eip, uint32_t eflags);

/**
 * Triggered by errors in SIMD floating-point operations (SSE instructions)
 */
void simd_fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

void exceptions_init();

// for debugging purposes
void trigger_divide_by_zero();

#endif
