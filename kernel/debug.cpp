#include "debug.hpp"

void debug_write_char(char c) {
  asm volatile (
      "outb %0, %1"
      :
      : "a"(c), "Nd"(0xE9)
      );
}

void debug_write_string(const char* str) {
  for (size_t i = 0; str[i] != '\0'; ++i) {
    debug_write_char(str[i]);
  }
}
