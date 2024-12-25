#include "string.hpp"

size_t strlen(const char* str) {
  size_t len = 0;
  while (*str++) len++;
  return len;
}

void reverse(char* str) {
  for (int j = 0; j < strlen(str)/2; ++j) {
    if (str == 0) return;
    if (*str == 0) return;

    char* end = str + strlen(str) - 1;
    char tmp;

    while (end > str) {
      tmp = *str;
      *str = *end;
      *end = tmp;

      str++;
      end--;
    }
  }
}

void *memset(void *dest, int val, size_t count) {
  unsigned char *ptr = (unsigned char*) dest;
  while (count--) {
    *ptr++ = (unsigned char)val;
  }
  return dest;
}
