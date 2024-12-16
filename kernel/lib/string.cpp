#include "string.hpp"

size_t strlen_(const char* str) {
  size_t len = 0;
  while (*str++) len++;
  return len;
}
