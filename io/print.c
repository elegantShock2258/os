#ifndef PRINT_C
#define PRINT_C

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum color {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHT_GREY = 7,
  DARK_GREY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN = 14,
  WHITE = 15,
};
static const size_t VGA_WIDTH = 192;
static const size_t VGA_HEIGHT = 108;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;
int _printinit = 0;

static inline uint8_t vga_entry_color(enum color fg, enum color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}
void TermInit(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(LIGHT_GREY, BLACK);
  terminal_buffer = (uint16_t *)0xB8000;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
  _printinit = 1;
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void _putchar(char c) {

  // if (!_printinit){
  //   TermInit();
  // } else {
	//   return ;
  // }

  if (c == '\n') {
    terminal_row++;
    terminal_column = 0;
    return ;
  }

  if (c == '\r') {
    terminal_column = 0;
    return ;
  }

  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT)
      terminal_row = 0;
  }
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    _putchar(data[i]);
}

void print(const char *data) { terminal_write(data, strlen(data)); }

void printChar(const char data) { _putchar(data); }

#endif
