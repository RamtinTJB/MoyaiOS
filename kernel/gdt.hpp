#ifndef MOYAIOS_GDT_HPP_
#define MOYAIOS_GDT_HPP_

#include <stdint.h>
#include <stddef.h>

// The maximum number of descriptors allowed: null, code, data
#define MAX_DESCRIPTORS                     3

// Set the access bit
#define GDT_DESC_ACCESS                     0x0001

// The descriptor is readable and writeable, the default is read only
#define GDT_DESC_READ_WRITE                 0x0002

// Expansion direction bit
#define GDT_DESC_EXPANSION                  0x0004

// The segment is executable
#define GDT_DESC_EXEC_CODE                  0x0008

// Code or data descriptor, the default is system defined descriptor
#define GDT_DESC_CODE_DATA                  0x0010

// DPL bits (Descriptor Privilege level): 11 is the lowest privilege
#define GDT_DESC_DPL                        0x0060

// "in memory" bit, basically means that the descriptor is valid
#define GDT_DESC_MEMORY                     0x0080



// High 4 bits of the limit
#define GDT_GRAN_LIMITHI_MASK               0x0f

// os defined bit
#define GDT_GRAN_OS                         0x10

// set if the section uses 32 bit addressing, the default is 16 bit
#define GDT_GRAN_32BIT                      0x40

// 4k granularity for the limit, the default is 1 byte
#define GDT_GRAN_4K                         0x80

struct gdt_entry {
  uint16_t limit;     // Bits 0-15 of segment limit
  uint16_t baseLo;    // Bits 0-15 of base address
  uint8_t  baseMid;   // Bits 16-23 of base address
  uint8_t  flags;     // access flags
  uint8_t  gran;      // granularity information
  uint8_t  baseHi;    // bits 24-32 of base address
} __attribute__((packed));

void gdt_set_descriptor(uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
gdt_entry *gdt_get_descriptor(int i);
int gdt_init();

#endif
