#include "pic.hpp"
#include "hw_interface.hpp"

void pic_send_command(uint8_t cmd, uint8_t pic) {
  if (pic > 1)
    return;

  uint16_t port = (pic == 0) ? PIC1_COMMAND_PORT : PIC2_COMMAND_PORT;
  outb(port, cmd);
}

void pic_send_data(uint8_t data, uint8_t pic) {
  if (pic > 1)
    return;

  uint16_t port = (pic == 0) ? PIC1_DATA_PORT : PIC2_DATA_PORT;
  outb(port, data);
}

uint8_t pic_read_data(uint8_t pic) {
  if (pic > 1)
    return 0;

  uint16_t port = (pic == 0) ? PIC1_DATA_PORT : PIC2_DATA_PORT;
  return inb(port);
}

void pic_init(uint8_t base0, uint8_t base1) {
    uint8_t icw = 0;

    disable();

    icw = (icw & ~PIC_ICW1_MASK_INIT) | PIC_ICW1_INIT_YES;
    icw = (icw & ~PIC_ICW1_MASK_IC4) | PIC_ICW1_IC4_EXPECT;

    // ICW1 - init + expect IC4
    pic_send_command(icw, 0);
    pic_send_command(icw, 1);

    // ICW2
    // sending interrupt vector address to master and slave PICs
    pic_send_data(base0, 0);
    pic_send_data(base1, 1);

    // ICW3
    // This is the connection between the master and slave PICs
    pic_send_data(4, 0);
    pic_send_data(2, 1);

    icw = (icw & ~PIC_ICW4_MASK_UPM) | PIC_ICW4_UPM_86MODE;

    // ICW4 - Enabling x86 mode
    pic_send_data(icw, 0);
    pic_send_data(icw, 1);
}
