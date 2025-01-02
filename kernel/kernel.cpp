#include "vga.hpp"
#include "gdt.hpp"
#include "idt.hpp"
#include "pic.hpp"
#include "pit.hpp"
#include "exceptions.hpp"
#include "hw_interface.hpp"
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
  idt_init(0x8);
  exceptions_init();
  pic_init(0x20, 0x28);
  pit_init();

  enable();

  terminal_init();
  const char* str = "Moyai OS";
  terminal_write(str, strlen(str));
  debug_write_string("Debug console from the C++ Kernel!\n");
  debug_printf("Welcome to %s, %d, %x\n", "Moyai OS", 100, str);

  //trigger_divide_by_zero();

  //gen_int(0x11);

  //while (1) {}
  //infinite_loop();
  for (;;) {
    debug_printf("Hello, World!\n");
    for (int i = 0; i < 1e7; ++i) {
      asm volatile ("nop");
    }
    //gen_int(0x11);
  }

  //gen_int(0x11);
}
