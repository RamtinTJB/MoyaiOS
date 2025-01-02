#include "pit.hpp"
#include "hw_interface.hpp"
#include <debug.hpp>

void pit_irq() {
    asm volatile(
        "add $12, %%esp\n\t"
        "pushal\n\t"
        :
        :
        : "memory"
    );

    debug_printf("PIT IRQ\n");
    interrupt_done(0);

    asm volatile(
        "popal\n\t"
        "iretl\n\t"
        :
        :
        : "memory"
    );
}

void pit_init() {
    set_int_vect(32, (I86_IRQ_HANDLER)pit_irq);
}