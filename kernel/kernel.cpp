#include "vga.hpp"
#include "gdt.hpp"
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

  gdt_init();

  terminal_init();
  const char* str = "Moyai OS";
  terminal_write(str, strlen(str));
  debug_write_string("Debug console from the C++ Kernel!\n");
  debug_printf("Welcome to %s, %d, %x\n", "Moyai OS", 100, str);

  while (1) {}
}
