#ifndef MOYAIOS_IDT_HPP_
#define MOYAIOS_IDT_HPP_

#include <stdint.h>

#define MAX_INTERRUPTS    256

#define IDT_DESC_BIT16    0x06
#define IDT_DESC_BIT32    0x0E
#define IDT_DESC_RING1    0x40
#define IDT_DESC_RING2    0x20
#define IDT_DESC_RING3    0x60
#define IDT_DESC_PRESENT  0x80

typedef void (__attribute__((cdecl)) *I86_IRQ_HANDLER)(void);

struct idt_entry {
  uint16_t baseLo;
  uint16_t sel;
  uint8_t  reserved;
  uint8_t  flags;
  uint16_t baseHi;
} __attribute__((packed));

idt_entry *get_ir(uint32_t i);
int install_ir(uint32_t i, uint16_t flags, uint16_t sel, I86_IRQ_HANDLER);
int idt_init(uint16_t codeSel);

void __attribute__((cdecl)) gen_int(int n);

#endif
