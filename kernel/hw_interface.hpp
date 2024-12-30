#ifndef MOYAIOS_HW_INTERFACE_
#define MOYAIOS_HW_INTERFACE_

#include <stdint.h>

void hardware_interface_init();

// Enable interrupts
void enable();

// Disable interrupts
void disable();

void outb(uint16_t portid, uint8_t value);
uint8_t inb(uint16_t portid);

#endif
