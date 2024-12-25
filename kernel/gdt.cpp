#include "gdt.hpp"
#include <string.hpp>

struct gdtr {
  uint16_t m_limit;   // Size of the GDT
  uint32_t m_base;    // Base address of GDT
} __attribute__((packed));

static struct gdt_entry  _gdt[MAX_DESCRIPTORS];
static struct gdtr       _gdtr;

static void gdt_install() {
  asm volatile ("lgdt (%0)" :: "r"(&_gdtr));
}

void gdt_set_descriptor(uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
  if (i > MAX_DESCRIPTORS)
    return;

  memset((void*)&_gdt[i], 0, sizeof(gdt_entry));
  
  _gdt[i].baseLo  = uint16_t(base & 0xffff);
  _gdt[i].baseMid = uint8_t((base >> 16) & 0xff);
  _gdt[i].baseHi  = uint8_t((base >> 24) & 0xff);
  _gdt[i].limit   = uint16_t(limit & 0xffff);

  _gdt[i].flags = access;
  _gdt[i].gran  = uint8_t((limit >> 16) & 0x0f);
  _gdt[i].gran |= gran & 0xf0;
}

gdt_entry *gdt_get_descriptor(int i) {
  if (i > MAX_DESCRIPTORS)
    return 0;

  return &_gdt[i];
}

int gdt_init() {
  _gdtr.m_limit = (sizeof (struct gdt_entry) * MAX_DESCRIPTORS) - 1;
  _gdtr.m_base  = (uint32_t)&_gdt[0];

  // Null Descriptor
  gdt_set_descriptor(0, 0, 0, 0, 0);

  // Code Descriptor
  gdt_set_descriptor(1, 0, 0xffffffff,
      GDT_DESC_READ_WRITE | GDT_DESC_EXEC_CODE | GDT_DESC_CODE_DATA | GDT_DESC_MEMORY,
      GDT_GRAN_4K | GDT_GRAN_32BIT | GDT_GRAN_LIMITHI_MASK);

  // Data Descriptor
  gdt_set_descriptor(2, 0, 0xffffffff,
      GDT_DESC_READ_WRITE | GDT_DESC_CODE_DATA | GDT_DESC_MEMORY,
      GDT_GRAN_4K | GDT_GRAN_32BIT | GDT_GRAN_LIMITHI_MASK);

  gdt_install();

  return 0;
}
