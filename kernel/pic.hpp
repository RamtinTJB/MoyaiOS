#ifndef MOYAIOS_PIC_HPP_
#define MOYAIOS_PIC_HPP_

#include <stdint.h>

// ====================== PIC I/O Ports ======================

// PIC 1 I/O ports
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT    0x21

// PIC 2 I/O ports
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT    0xA1

// ====================== Operation Command Words ======================

// Command word 2 bit masks
#define PIC_OCW2_MASK_L1        1         // Interrupt level 1
#define PIC_OCW2_MASK_L2        2         // Interrupt level 2
#define PIC_OCW2_MASK_L3        4         // Interrupt level 3
#define PIC_OCW2_MASK_EOI       0x20      // End of Interrupt mask
#define PIC_OCW2_MASK_SL        0x40      // Selection
#define PIC_OCW2_MASK_ROTATE    0x80      // Rotation option

// Command word 3 bit masks
#define PIC_OCW3_MASK_RIS       1
#define PIC_OCW3_MASK_RIR       2
#define PIC_OCW3_MASK_MODE      4
#define PIC_OCW3_MASK_SMM       0x20
#define PIC_OCW3_MASK_ESMM      0x40
#define PIC_OCW3_MASK_D7        0x80

// ====================== Initialization Command Words ======================
#define PIC_ICW1_MASK_IC4       1         // If set, PIC will expect Initialization command 4
#define PIC_ICW1_MASK_SNGL      2         // If = 1, there is only one PIC in the system
#define PIC_ICW1_MASK_ADI       4         // Ignored by x86 systems
#define PIC_ICW1_MASK_LTIM      8         // If set, PIC will operate in Level Triggered Mode
#define PIC_ICW1_MASK_INIT      0x10      // Initialization bit

#define PIC_ICW4_MASK_UPM       1         // Has to be set in x86 mode
#define PIC_ICW4_MASK_AEOI      2         // If set, controlle automatically performs End of
                                          // Interrupt (EOI) operation on the last interrupt acknowledge pulse
#define PIC_ICW4_MASK_MS        4         // use buffer master (use onl when buf is set)
#define PIC_ICW4_MASK_BUF       8         // If set, operate in buffer mode
#define PIC_ICW4_MASK_SFNM      0x10      // special fully nested mode

#define PIC_ICW1_IC4_EXPECT             1
#define PIC_ICW1_IC4_NO                 0
#define PIC_ICW1_SNGL_YES               2
#define PIC_ICW1_SNGL_NO                0
#define PIC_ICW1_ADI_CALLINTERVAL4      4
#define PIC_ICW1_ADI_CALLINTERVAL8      0
#define PIC_ICW1_LTIM_LEVELTRIGGERED    8
#define PIC_ICW1_LTIM_EDGETRIGGERED     0
#define PIC_ICW1_INIT_YES               0x10
#define PIC_ICW1_INIT_NO                0

#define PIC_ICW4_UPM_86MODE             1
#define PIC_ICW4_UPM_MCSMODE            0
#define PIC_ICW4_AEOI_AUTOEOI           2
#define PIC_ICW4_AEOI_NOAUTOEOI         0
#define PIC_ICW4_MS_BUFFERMASTER        4
#define PIC_ICW4_MS_BUFFERSLAVE         0
#define PIC_ICW4_BUF_MODEYES            8
#define PIC_ICW4_BUF_MODENO             0
#define PIC_ICW4_SFNM_NESTEDMODE        0x10
#define PIC_ICW4_SFNM_NOTNESTED         0


// ====================== PIC IRQs ======================

// These devices use the master PIC to generate interrupts
#define PIC_IRQ_TIMER           0
#define PIC_IRQ_KEYBOARD        1
#define PIC_IRQ_CASCADE         2
#define PIC_IRQ_COM2            3
#define PIC_IRQ_COM1            4
#define PIC_IRQ_LPT2            5
#define PIC_IRQ_FLOPPY          6
#define PIC_IRQ_LPT1            7

// These devices use the slave PIC to generate interrupts
#define PIC_IRQ_CMOS            0
#define PIC_IRQ_CGA             1
#define PIC_IRQ_AUX             4
#define PIC_IRQ_FPU             5
#define PIC_IRQ_HDC             6



uint8_t pic_read_data(uint8_t pic);
void pic_send_data(uint8_t data, uint8_t pic);
void pic_send_command(uint8_t cmd, uint8_t pic);
void pic_mask_irq(uint8_t irq_mask, uint8_t pic);
void pic_init(uint8_t base0, uint8_t base1);

#endif
