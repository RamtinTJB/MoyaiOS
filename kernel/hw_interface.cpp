#include "hw_interface.hpp"
#include "pic.hpp"

void enable() {
  asm volatile ("sti");
}

void disable() {
  asm volatile ("cli");
}

void outb(uint16_t portid, uint8_t value) {
  asm volatile(
      "outb %0, %1"
      :
      : "a" (value), "Nd" (portid)
    );
}

uint8_t inb(uint16_t portid) {
  uint8_t value;
  asm volatile (
    "inb %1, %0"
    : "=a" (value)
    : "Nd" (portid)
  );
  return value;
}

void set_int_vect(int intno, I86_IRQ_HANDLER handler) {
  install_ir(intno, IDT_DESC_PRESENT | IDT_DESC_BIT32,
      0x8, handler);
}

I86_IRQ_HANDLER get_int_vect(int intno) {
  idt_entry* entry = get_ir(intno);
  if (!entry)
    return 0;

  uint32_t addr = entry->baseLo | (entry->baseHi << 16);

  return (I86_IRQ_HANDLER)addr;
}

void interrupt_done(uint8_t intno) {
  if (intno > 16)
    return;

  if (intno >= 8)
    pic_send_command(PIC_OCW2_MASK_EOI, 1);

  pic_send_command(PIC_OCW2_MASK_EOI, 0);
}
