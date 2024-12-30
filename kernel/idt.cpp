#include "idt.hpp"
#include <string.hpp>
#include <debug.hpp>

struct idtr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

static struct idt_entry _idt[MAX_INTERRUPTS];
static struct idtr      _idtr;

static void idt_install() {
  // lidt [_idtr]
  asm volatile ("lidt (%0)" :: "r"(&_idtr));
}

static void i86_default_handler() {
  debug_printf("i86_default_handler: Unhandled Exception");
  for (;;);
}

idt_entry *get_ir(uint32_t i) {
  if (i > MAX_INTERRUPTS)
    return 0;

  return &_idt[i];
}

int install_ir(uint32_t i, uint16_t flags, uint16_t sel, I86_IRQ_HANDLER irq) {
  if (i > MAX_INTERRUPTS)
    return 0;

  if (!irq)
    return 0;

  uint64_t uiBase = (uint64_t)&(*irq);

  _idt[i].baseLo    = uint16_t(uiBase & 0xffff);
  _idt[i].baseHi    = uint16_t((uiBase >> 16) & 0xffff);
  _idt[i].reserved  = 0;
  _idt[i].flags     = uint8_t(flags);
  _idt[i].sel       = sel;

  return 0;
}

int idt_init(uint16_t codeSel) {
  _idtr.limit = sizeof (struct idt_entry) * MAX_INTERRUPTS - 1;
  _idtr.base  = (uint32_t)&_idt[0];

  // zero out the idt table before populating
  memset((void*)&_idt[0], 0, sizeof(idt_entry) * MAX_INTERRUPTS - 1);

  for (int i = 0; i < MAX_INTERRUPTS; ++i) {
    install_ir(i, IDT_DESC_PRESENT | IDT_DESC_BIT32,
        codeSel, (I86_IRQ_HANDLER)i86_default_handler);
  }

  idt_install();

  return 0;
}

void __attribute__((cdecl)) gen_int(int n) {
  __asm__ (
    "movb %[n], %%al\n\t"        // Load the value of 'n' into AL
    "movb %%al, genint+1\n\t"    // Write AL to 'genint+1' (modify the interrupt number)
    "jmp genint\n\t"             // Jump to 'genint'
    "genint:\n\t"
    "int $0\n\t"                 // Execute the interrupt
    :
    : [n] "m" (n)                // Input: 'n' is a memory operand
    : "al"                       // Clobber: AL is modified
  );
}
