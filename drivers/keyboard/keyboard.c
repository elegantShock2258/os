// TODO: write a full-fleged keyboard driver
#pragma once

#include "../../arch/i686/hal/interrupts/isr/isr.h"
#include "../../arch/i686/hal/io/serial.c"
#include "../../arch/i686/hal/io/printf.c"

#define KEYBOARD_DATA_PORT 0x60

#define BUFFER_MAX 100000

int keyboard_irq_handled = 0;
unsigned char keyboard_buffer[BUFFER_MAX];
int keyboard_buffer_pointer = 0;
unsigned char lc;
unsigned char keyboard_read_scan_code(void) { return inb(KEYBOARD_DATA_PORT); }

unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code) {
  unsigned char ascii[256] = {
      0x0,  0x0, '1', '2',  '3',  '4', '5', '6', // 0 - 7
      '7',  '8', '9', '0',  '-',  '=', 0x0, 0x0, // 8 - 15
      'q',  'w', 'e', 'r',  't',  'y', 'u', 'i', // 16 - 23
      'o',  'p', '[', ']',  '\n', 0x0, 'a', 's', // 24 - 31
      'd',  'f', 'g', 'h',  'j',  'k', 'l', ';', // 32 - 39
      '\'', '`', 0x0, '\\', 'z',  'x', 'c', 'v', // 40 - 47
      'b',  'n', 'm', ',',  '.',  '/', 0x0, '*', // 48 - 55
      0x0,  ' ', 0x0, 0x0,  0x0,  0x0, 0x0, 0x0, // 56 - 63
      0x0,  0x0, 0x0, 0x0,  0x0,  0x0, 0x0, '7', // 64 - 71
      '8',  '9', '-', '4',  '5',  '6', '+', '1', // 72 - 79
      '2',  '3', '0', '.'                        // 80 - 83
  };

  return ascii[scan_code];
}

void keyboard(Registers *regs) {
  unsigned char scancode = keyboard_read_scan_code();
  unsigned char code = keyboard_scan_code_to_ascii(scancode);
  printf("%c %d\n",code,scancode);  
  if(scancode >= 0x80) return; // ignore above 0x80

  keyboard_buffer[keyboard_buffer_pointer] = code;
  keyboard_buffer_pointer = (keyboard_buffer_pointer + 1) % BUFFER_MAX;

  keyboard_irq_handled = 1;
  // if (code == '\n') {
  //   terminal_row++;
  //   terminal_column = 0;
  //   setcursor(terminal_column, terminal_row);
  //   return;
  // }
  // if (scancode == 0x0E) {
  //   terminal_column--;
  //   terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
  //   setcursor(terminal_column, terminal_row);
  //   return;
  // }
  // if (scancode == 0xE0) {
  //   scrollback(1);
  //   setcursor(terminal_column, terminal_row);
  // }
  // printf("%c", code); // TODO: send code to outb.
}