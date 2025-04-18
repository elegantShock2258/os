#pragma once
#include "../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../arch/i686/hal/interrupts/isr/isr.h"
#include "../../arch/i686/hal/io/printf.c"
#include "../../arch/i686/hal/io/serial.c"

#include "../../utils/ds/buffer/buffer.c"

typedef struct {
  struct {
    int control, alt, shift, gui;
  } left;

  struct {
    int control, alt, shift, gui;
  } right;

  int altGr; // usually right alt (0xE0 0x38)

  int functionKeys[12]; // F1 to F12
  int backspace;
  int tab;
  int enter;
  int capsLock;
  int escape;
  int space;
  int meta; // "apps" key

  struct {
    int scrollLock, capsLock, numLock;
  } locks;

  struct {
    int up, down, left, right;
    int home, end, insert, delete;
    int pageUp, pageDown;
  } arrows;

  struct {
    int printScreen;
    int pause;
  } system;

  struct {
    int enter;
    int divide, multiply, subtract, add;
    int dot;
    int numbers[10]; // keypad 0-9
  } keypad;

  struct {
    int mute, volumeUp, volumeDown;
    int play, stop, next, previous;
  } multimedia;

  struct {
    int calculator, email, home, search;
    int favorites, refresh, stop;
    int forward, back;
    int mediaSelect, myComputer;
  } browser;

  struct {
    int power, sleep, wake;
  } acpi;
} SpecialKeys;

typedef struct {
  int keyboard_irq_handled;
  CircularBuffer keyboard_buffer;
  unsigned char lc;
  SpecialKeys *specialKeys;
  unsigned char *releaseMap;

  unsigned char (*keyboard_read_scan_code)(void);
  unsigned char (*keyboard_scan_code_to_ascii)(unsigned char scan_code);
  void (*keyboard)(Registers *regs);
  void (*Constructor)();

} KeyboardDriverState;

#define KEYBOARD_DATA_PORT 0x60
#define BUFFER_MAX 100
