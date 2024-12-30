#include "hw_interface.hpp"

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
