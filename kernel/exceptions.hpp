#ifndef MOYAIOS_EXCEPTIONS_HPP_
#define MOYAIOS_EXCEPTIONS_HPP_

#include <stdint.h>

void kernel_panic(const char* msg);

void divide_by_zero_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

void exceptions_init();

// for debugging purposes
void trigger_divide_by_zero();

#endif
