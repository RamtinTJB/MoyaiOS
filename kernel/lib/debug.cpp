#include "debug.hpp"
#include "string.hpp"
#include "../hw_interface.hpp"

void debug_write_char(char c) {
  /* asm volatile ( */
  /*     "outb %0, %1" */
  /*     : */
  /*     : "a"(c), "Nd"(0xE9) */
  /*     ); */
  outb(0xE9, c);
}

void debug_write_string(const char* str) {
  for (size_t i = 0; str[i] != '\0'; ++i) {
    debug_write_char(str[i]);
  }
}

static void print_decimal(int value) {
    char buffer[12]; // Enough to hold -2^31 and '\0'
    bool negative = (value < 0);

    if (negative) {
        value = -value;
    }

    int i = 0;
    do {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    if (negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    reverse(buffer);

    debug_write_string(buffer);
}

static void print_hex(unsigned int value) {
    char buffer[9]; // Enough to hold 8 hex digits and '\0' (32 bit addressing)
    const char* hex_digits = "0123456789ABCDEF";

    int i = 0;
    do {
        buffer[i++] = hex_digits[value % 16];
        value /= 16;
    } while (value > 0);

    while (i < 8) {
        buffer[i++] = '0'; // Zero-pad for fixed width
    }

    buffer[i] = '\0';
    reverse(buffer);

    debug_write_string("0x");
    debug_write_string(buffer);
}

void debug_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (size_t i = 0; format[i] != '\0'; ++i) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            ++i;
            switch (format[i]) {
                case 's': { // String
                    const char* str = va_arg(args, const char*);
                    debug_write_string(str);
                    break;
                }
                case 'd': { // Decimal
                    int value = va_arg(args, int);
                    print_decimal(value);
                    break;
                }
                case 'x': { // Hexadecimal
                    unsigned int value = va_arg(args, unsigned int);
                    print_hex(value);
                    break;
                }
                case 'c': { // Character
                    char c = (char)va_arg(args, int);
                    debug_write_char(c);
                    break;
                }
                default:
                    debug_write_char('%');
                    debug_write_char(format[i]);
                    break;
            }
        } else {
            debug_write_char(format[i]);
        }
    }

    va_end(args);
}

void infinite_loop() {
    asm volatile ("1: hlt; jmp 1b");
}