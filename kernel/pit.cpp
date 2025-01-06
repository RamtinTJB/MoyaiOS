#include "pit.hpp"
#include "hw_interface.hpp"
#include <debug.hpp>

static uint32_t tick_count = 0;

extern "C" void pit_irq_handler();

extern "C" __attribute__((naked)) void pit_irq() {
    // asm volatile(
    //     "cli\n\t"
    //     "pushal\n\t"
    //     :
    //     :
    //     : "memory"
    // );

    // debug_printf("PIT IRQ\n");
    // tick_count++;
    // interrupt_done(0);

    // asm volatile("sti");
    // asm volatile(
    //     "popal\n\t"
    //     "iretl\n\t"
    //     :
    //     :
    //     : "memory"
    // );
    __asm__ volatile(
        "cli\n\t"
        "pushal\n\t"
        "call pit_irq_handler\n\t"
        "popal\n\t"
        "iret\n\t"
    );
}

extern "C" void pit_irq_handler() {
  debug_printf("PIT_IRQ\n");
  tick_count++;
  interrupt_done(0);
}

void pit_send_command(uint8_t cmd) {
  outb(PIT_REG_COMMAND, cmd);
}

void pit_send_data(uint16_t data, uint8_t counter) {
  uint8_t port;
  if (counter == PIT_OCW_COUNTER_0) port = PIT_REG_COUNTER0;
  else if (counter == PIT_OCW_COUNTER_1) port = PIT_REG_COUNTER1;
  else if (counter == PIT_OCW_COUNTER_2) port = PIT_REG_COUNTER2;
  else return;

  outb(port, (uint8_t)data);
}

uint8_t pit_read_data(uint16_t counter) {
  uint8_t port;
  if (counter == PIT_OCW_COUNTER_0) port = PIT_REG_COUNTER0;
  else if (counter == PIT_OCW_COUNTER_1) port = PIT_REG_COUNTER1;
  else if (counter == PIT_OCW_COUNTER_2) port = PIT_REG_COUNTER2;
  else return 0;

  return inb(port);
}

void pit_start_counter(uint32_t frequency, uint8_t counter, uint8_t mode) {
  if (frequency == 0) return;

  uint16_t div = uint16_t(1193181 / (uint16_t)frequency);

  uint8_t ocw = 0;
  ocw = (ocw & ~PIT_OCW_MASK_MODE) | mode;
  ocw = (ocw & ~PIT_OCW_MASK_RL) | PIT_OCW_RL_DATA;
  ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | counter;
  pit_send_command(ocw);

  pit_send_data(div & 0xff, 0);
  pit_send_data((div >> 8) & 0xff, 0);

  tick_count = 0;
}

uint32_t pit_get_tick_count() {
  return tick_count;
}

void pit_init() {
    set_int_vect(32, (I86_IRQ_HANDLER)pit_irq);
    pit_start_counter(100, PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVE);
}
