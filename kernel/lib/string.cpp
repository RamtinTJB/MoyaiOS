#include "string.hpp"

size_t strlen(const char* str) {
  size_t len = 0;
  while (*str++) len++;
  return len;
}

void reverse(char* str) {
  if (!str) return;
  size_t len = strlen(str);
  if (len <= 1) return;

  for (size_t i = 0; i < len / 2; ++i) {
    char tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  }
}

void *memset(void *dest, int val, size_t count) {
  unsigned char *ptr = (unsigned char*) dest;
  while (count--) {
    *ptr++ = (unsigned char)val;
  }
  return dest;
}
