// TODO: write a full-fleged keyboard driver
#pragma once

#include "./keyboard.h"

KeyboardDriverState  KeyboardDriver;

unsigned char _Keyboard_t[BUFFER_MAX];
SpecialKeys _Keyboard_specialKeys;

unsigned char _Keyboard_read_scan_code(void) { return inb(KEYBOARD_DATA_PORT); }

unsigned char _Keyboard_scan_code_to_ascii(unsigned char scan_code) {
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

void _Keyboard(Registers *regs) {
  unsigned char scancode = _Keyboard_read_scan_code();
  unsigned char code = _Keyboard_scan_code_to_ascii(scancode);
  printf("%c %d\n", code, scancode);
  if (scancode >= 0x80)
    return; // ignore above 0x80
  // TODO: update special keys whenever the keys are pressed.

  KeyboardDriver.keyboard_buffer[KeyboardDriver.keyboard_buffer_pointer] = code;
  KeyboardDriver.keyboard_buffer_pointer = (KeyboardDriver.keyboard_buffer_pointer + 1) % BUFFER_MAX;

  KeyboardDriver.keyboard_irq_handled = !KeyboardDriver.keyboard_irq_handled;
  // asm("mov $0x42, %edx");
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


void KeyboardConstructor() {

  KeyboardDriver.keyboard_irq_handled = 0;
  KeyboardDriver.keyboard_buffer_pointer = 0;
  KeyboardDriver.keyboard_buffer = _Keyboard_t;
  KeyboardDriver.lc = ' ';
  KeyboardDriver.scancode = 0;
  KeyboardDriver.code = 0;
  KeyboardDriver.keyboard_buffer_pointer = 0;
  KeyboardDriver.keyboard_irq_handled = 0;
  KeyboardDriver.specialKeys = &_Keyboard_specialKeys;


  KeyboardDriver.keyboard_read_scan_code = _Keyboard_read_scan_code;
  KeyboardDriver.keyboard_scan_code_to_ascii = _Keyboard_scan_code_to_ascii;
  KeyboardDriver.keyboard = _Keyboard;

  KeyboardDriver.Constructor = KeyboardConstructor;

  IRQ_RegisterHandler(1,KeyboardDriver.keyboard);
}
