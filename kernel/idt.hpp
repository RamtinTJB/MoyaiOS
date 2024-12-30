#ifndef MOYAIOS_IDT_HPP_
#define MOYAIOS_IDT_HPP_

#include <stdint.h>

// ================== IDT Descriptor Flags ==================

// Maximum number of entries in the IDT
#define MAX_INTERRUPTS    256

// 16-bit interrupt gate
#define IDT_DESC_BIT16    0x06

// 32-bit interrupt gate
#define IDT_DESC_BIT32    0x0E

// Interrupt gate accessible at privilege level 1
#define IDT_DESC_RING1    0x40

// Interrupt gate accessible at privilege level 2
#define IDT_DESC_RING2    0x20

// Interrupt gate accessible at privilege level 3
#define IDT_DESC_RING3    0x60

// Interrupt gate is present in memory
#define IDT_DESC_PRESENT  0x80

/*
 * Defined a pointer to an interrupt handler function
 * All interrupt handlers must conform to this calling convention
 *
 * Note: cdelc is a compiler specific attribute that indicates
 *      that C calling convention must be used
 */
typedef void (__attribute__((cdecl)) *I86_IRQ_HANDLER)(void);

// ================== IDT Entry Structure ==================

struct idt_entry {
  uint16_t baseLo;      // Low 16 bits of handler function address
  uint16_t sel;         // Segment selector
  uint8_t  reserved;    // Reserved field (set to 0)
  uint8_t  flags;       // Descriptor flags
  uint16_t baseHi;      // High 16 bit of the handler function address
} __attribute__((packed));

// ================== IDT Functions ==================

idt_entry *get_ir(uint32_t i);
int install_ir(uint32_t i, uint16_t flags, uint16_t sel, I86_IRQ_HANDLER);
int idt_init(uint16_t codeSel);

// Generate the interrupt n
// Same as calling [int n] in assmebly
void __attribute__((cdecl)) gen_int(int n);

#endif // MOYAIOS_IDT_HPP_
