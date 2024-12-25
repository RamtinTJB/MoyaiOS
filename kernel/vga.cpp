#include "vga.hpp"

static uint16_t* video_memory = (uint16_t*)0xB8000;

size_t term_row;
size_t term_col;
uint8_t term_color;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t) color << 8;
}

static const size_t WIDTH = 80;
static const size_t HEIGHT = 25;

void terminal_init(void) {
  term_row = 0;
  term_col = 0;
  term_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

  for (size_t y = 0; y < HEIGHT; ++y) {
    for (size_t x = 0; x < WIDTH; ++x) {
      const size_t index = y*WIDTH + x;
      video_memory[index] = vga_entry(' ', term_color);
    }
  }
}

void terminal_setcolor(uint8_t color) {
  term_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y*WIDTH + x;
  video_memory[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
  terminal_putentryat(c, term_color, term_col, term_row);
  if (++term_col == WIDTH) {
    term_col = 0;
    if (++term_row == HEIGHT)
      term_row = 0;
  }
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    terminal_putchar(data[i]);
  }
}

void putchar(char c) {
  video_memory[0] = c;
  video_memory[1] = 0x8;
}
