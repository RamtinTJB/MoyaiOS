#include "exceptions.hpp"
#include <debug.hpp>
#include "hw_interface.hpp"

void kernel_panic(const char* msg) {
  debug_printf("*** STOP: %s\n", msg);
}

void divide_by_zero_fault(uint32_t cs, uint32_t eip, uint32_t eflags) {
  kernel_panic("Divide by 0");
  for (;;);
}

void set_int_vect(int intno, I86_IRQ_HANDLER handler) {
  install_ir(intno, IDT_DESC_PRESENT | IDT_DESC_BIT32,
      0x8, handler);
}

void exceptions_init() {
  set_int_vect(0, (I86_IRQ_HANDLER)divide_by_zero_fault);
}

void trigger_divide_by_zero() {
  volatile int zero = 0;
  volatile int one = 1;
  int result = one/zero;
  (void)result;
}
