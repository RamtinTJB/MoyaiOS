#ifndef MOYAIOS_HW_INTERFACE_
#define MOYAIOS_HW_INTERFACE_

#include <stdint.h>
#include "idt.hpp"

void hardware_interface_init();

// Enable interrupts
void enable();

// Disable interrupts
void disable();

void outb(uint16_t portid, uint8_t value);
uint8_t inb(uint16_t portid);

void set_int_vect(int intno, I86_IRQ_HANDLER);
I86_IRQ_HANDLER get_int_vect(int intno);

void interrupt_done(uint8_t intno);

#endif
