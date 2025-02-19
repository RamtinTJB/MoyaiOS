#ifndef MOYAIOS_PIT_HPP_
#define MOYAIOS_PIT_HPP_

#include <stdint.h>

// ====================== PIT I/O Ports ======================
#define PIT_REG_COUNTER0            0x40
#define PIT_REG_COUNTER1            0x41
#define PIT_REG_COUNTER2            0x42
#define PIT_REG_COMMAND             0x43

// ====================== Operational Command Bit masks ======================
#define PIT_OCW_MASK_BINCOUNT       1
#define PIT_OCW_MASK_MODE           0xE
#define PIT_OCW_MASK_RL             0x30
#define PIT_OCW_MASK_COUNTER        0xC0

// ====================== Control Bits ======================

// Binary count mode
#define PIT_OCW_BINCOUNT_BINARY     0
#define PIT_OCW_BINCOUNT_BCD        1

// Counter mode
#define PIT_OCW_MODE_TERMINALCOUNT  0
#define PIT_OCW_MODE_ONESHOT        0x2
#define PIT_OCW_MODE_RATEGEN        0x4
#define PIT_OCW_MODE_SQUAREWAVE     0x6
#define PIT_OCW_MODE_SOFTWARETRIG   0x8
#define PIT_OCW_MODE_HARDWARETRIG   0xA

// Data transfer
#define PIT_OCW_RL_LATCH            0
#define PIT_OCW_RL_LSBONLY          0x10
#define PIT_OCW_RL_MSBONLY          0x20
#define PIT_OCW_RL_DATA             0x30

// The counter we are working with
#define PIT_OCW_COUNTER_0           0
#define PIT_OCW_COUNTER_1           0x40
#define PIT_OCW_COUNTER_2           0x80

void pit_send_command(uint8_t cmd);
void pit_send_data(uint16_t data, uint8_t counter);
uint8_t pit_read_data(uint16_t counter);
uint32_t pit_get_tick_count();
void pit_start_counter(uint32_t frequency, uint8_t counter, uint8_t mode);

void pit_init();

#endif
