#include "vga.hpp"
#include <debug.hpp>
#include <string.hpp>

extern "C" void kernel_main() {
  asm volatile (
        "mov $0x10, %%ax\n"  // DATA_DESC (GDT index 0x10)
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :
        :
        : "ax"

    );

  terminal_init();
  const char* str = "Moyai OS";
  terminal_write(str, strlen_(str));
  debug_write_string("Debug console from the C++ Kernel!\n");

  while (1) {}
}
