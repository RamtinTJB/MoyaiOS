#ifndef MOYAIOS_DEBUG_HPP_
#define MOYAIOS_DEBUG_HPP_

#include <stddef.h>
#include <stdarg.h>

void debug_write_char(char c);
void debug_write_string(const char* str);
void debug_printf(const char* format, ...);

void infinite_loop();

#endif
