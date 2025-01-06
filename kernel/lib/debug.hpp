#ifndef MOYAIOS_DEBUG_HPP_
#define MOYAIOS_DEBUG_HPP_

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

void debug_write_char(char c);
void debug_write_string(const char* str);
void debug_printf(const char* format, ...);

void print_cs();
void print_eip();
void print_stack(uint32_t n);
void print_function_address(void*);

void infinite_loop();

#endif
