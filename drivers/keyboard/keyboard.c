// TODO: write a full-fleged keyboard driver
#pragma once

#include "./keyboard.h"
#include "../../drivers/vbe/vbe.c"

KeyboardDriverState KeyboardDriver;
CircularBuffer _Keyoard_CircularBuffer;

static SpecialKeys _Keyboard_specialKeys;
static unsigned char _Keyboard_Release_map[256] = {0};
static bool extended = false;

static unsigned char ascii[256] = {
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

static void _Keyboard_update_special_keys(uint8_t scancode, bool released,
                                          bool is_extended) {
  uint8_t key = scancode & 0x7F;

  if (!is_extended) {
    switch (key) {
    case 0x1D:
      _Keyboard_specialKeys.left.control = !released;
      break;
    case 0x38:
      _Keyboard_specialKeys.left.alt = !released;
      break;
    case 0x2A:
      _Keyboard_specialKeys.left.shift = !released;
      break;
    case 0x36:
      _Keyboard_specialKeys.right.shift = !released;
      break;
    case 0x0E:
      _Keyboard_specialKeys.backspace = !released;
      break;
    case 0x0F:
      _Keyboard_specialKeys.tab = !released;
      break;
    case 0x1C:
      _Keyboard_specialKeys.enter = !released;
      break;
    case 0x3A:
      _Keyboard_specialKeys.capsLock = !released;
      _Keyboard_specialKeys.locks.capsLock = !released;
      break;
    case 0x01:
      _Keyboard_specialKeys.escape = !released;
      break;
    case 0x39:
      _Keyboard_specialKeys.space = !released;
      break;
    case 0x45:
      _Keyboard_specialKeys.locks.numLock = !released;
      break;
    case 0x46:
      _Keyboard_specialKeys.locks.scrollLock = !released;
      break;

    case 0x3B ... 0x44:
      _Keyboard_specialKeys.functionKeys[key - 0x3B] = !released;
      break;
    case 0x57:
      _Keyboard_specialKeys.functionKeys[10] = !released;
      break;
    case 0x58:
      _Keyboard_specialKeys.functionKeys[11] = !released;
      break;
    }
  } else {
    switch (key) {
    case 0x1D:
      _Keyboard_specialKeys.right.control = !released;
      break;
    case 0x38:
      _Keyboard_specialKeys.right.alt = !released;
      _Keyboard_specialKeys.altGr = !released;
      break;
    case 0x5B:
      _Keyboard_specialKeys.left.gui = !released;
      break;
    case 0x5C:
      _Keyboard_specialKeys.right.gui = !released;
      break;
    case 0x5D:
      _Keyboard_specialKeys.meta = !released;
      break;

    case 0x47:
      _Keyboard_specialKeys.arrows.home = !released;
      break;
    case 0x4F:
      _Keyboard_specialKeys.arrows.end = !released;
      break;
    case 0x52:
      _Keyboard_specialKeys.arrows.insert = !released;
      break;
    case 0x53:
      _Keyboard_specialKeys.arrows.delete = !released;
      break;
    case 0x49:
      _Keyboard_specialKeys.arrows.pageUp = !released;
      break;
    case 0x51:
      _Keyboard_specialKeys.arrows.pageDown = !released;
      break;
    case 0x48:
      _Keyboard_specialKeys.arrows.up = !released;
      break;
    case 0x50:
      _Keyboard_specialKeys.arrows.down = !released;
      break;
    case 0x4B:
      _Keyboard_specialKeys.arrows.left = !released;
      break;
    case 0x4D:
      _Keyboard_specialKeys.arrows.right = !released;
      break;

    case 0x35:
      _Keyboard_specialKeys.keypad.divide = !released;
      break;
    case 0x1C:
      _Keyboard_specialKeys.keypad.enter = !released;
      break;

    case 0x5E:
      _Keyboard_specialKeys.acpi.power = !released;
      break;
    case 0x5F:
      _Keyboard_specialKeys.acpi.sleep = !released;
      break;
    case 0x63:
      _Keyboard_specialKeys.acpi.wake = !released;
      break;

    case 0x20:
      _Keyboard_specialKeys.multimedia.mute = !released;
      break;
    case 0x30:
      _Keyboard_specialKeys.multimedia.volumeUp = !released;
      break;
    case 0x2E:
      _Keyboard_specialKeys.multimedia.volumeDown = !released;
      break;
    case 0x22:
      _Keyboard_specialKeys.multimedia.play = !released;
      break;
    case 0x24:
      _Keyboard_specialKeys.multimedia.stop = !released;
      break;
    case 0x19:
      _Keyboard_specialKeys.multimedia.next = !released;
      break;
    case 0x10:
      _Keyboard_specialKeys.multimedia.previous = !released;
      break;

    case 0x21:
      _Keyboard_specialKeys.browser.calculator = !released;
      break;
    case 0x6C:
      _Keyboard_specialKeys.browser.email = !released;
      break;
    case 0x32:
      _Keyboard_specialKeys.browser.home = !released;
      break;
    case 0x65:
      _Keyboard_specialKeys.browser.search = !released;
      break;
    case 0x66:
      _Keyboard_specialKeys.browser.favorites = !released;
      break;
    case 0x67:
      _Keyboard_specialKeys.browser.refresh = !released;
      break;
    case 0x68:
      _Keyboard_specialKeys.browser.stop = !released;
      break;
    case 0x69:
      _Keyboard_specialKeys.browser.forward = !released;
      break;
    case 0x6A:
      _Keyboard_specialKeys.browser.back = !released;
      break;
    case 0x6D:
      _Keyboard_specialKeys.browser.mediaSelect = !released;
      break;
    case 0x6B:
      _Keyboard_specialKeys.browser.myComputer = !released;
      break;
    }
  }
}

unsigned char _Keyboard_read_scan_code(void) { return inb(KEYBOARD_DATA_PORT); }

unsigned char _Keyboard_scan_code_to_ascii(unsigned char scan_code) {
  return ascii[scan_code];
}

unsigned char _Keyboard_get_char() {
  unsigned char _top =
      (KeyboardDriver.keyboard_buffer.top(&KeyboardDriver.keyboard_buffer));
  if (_Keyboard_Release_map[_top]) {
    return _top;
  } else {
    unsigned char t = _top;
    KeyboardDriver.keyboard_buffer.dequeue(&KeyboardDriver.keyboard_buffer,
                                           &_top);
    return t;
  }
}

void _Keyboard(Registers *regs) {
  unsigned char scancode = _Keyboard_read_scan_code();
  unsigned char code = _Keyboard_scan_code_to_ascii(scancode);
  printf("KEYBOARD: %c %d\n", code, scancode);

  // TODO: update special keys whenever the keys are pressed.
  // TODO: do holding keys and all.
  if (scancode == 0xE0) {
    extended = true;
    return;
  }

  bool released = (scancode & 0x80);
  uint8_t key = scancode & 0x7F; // scancode - 128
  if (!extended) {
    if (released) {
      // key is released
      _Keyboard_Release_map[scancode - 0x80] = false;
    } else {
      // key is pressed
      _Keyboard_Release_map[scancode] = true;
      KeyboardDriver.keyboard_buffer.enqueue(&KeyboardDriver.keyboard_buffer,
                                             scancode);
      KeyboardDriver.keyboard_irq_handled = 1;
    }
  }
  _Keyboard_update_special_keys(scancode, released, extended);

  extended = false;
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
  // printf("%c", code); // TODO: send code to outb?.
}

void KeyboardConstructor() {

  KeyboardDriver.keyboard_irq_handled = 0;
  KeyboardDriver.lc = ' ';
  KeyboardDriver.keyboard_buffer = _Keyoard_CircularBuffer;
  KeyboardDriver.specialKeys = &_Keyboard_specialKeys;

  KeyboardDriver.keyboard_read_scan_code = _Keyboard_read_scan_code;
  KeyboardDriver.keyboard_scan_code_to_ascii = _Keyboard_scan_code_to_ascii;
  KeyboardDriver.keyboard = _Keyboard;
  KeyboardDriver.releaseMap = _Keyboard_Release_map;

  KeyboardDriver.Constructor = KeyboardConstructor;

  _CB_Constructor(&KeyboardDriver.keyboard_buffer, BUFFER_MAX);
  IRQ_RegisterHandler(1, KeyboardDriver.keyboard);
}
