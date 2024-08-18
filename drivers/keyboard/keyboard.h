#pragma once
#include "../../arch/i686/hal/interrupts/isr/isr.h"
#include "../../arch/i686/hal/io/printf.c"
#include "../../arch/i686/hal/io/serial.c"
#include "../../arch/i686/hal/interrupts/irq/irq.c"
typedef struct {
    struct {int control,alt,shift;} left;
    struct {int control,alt,shift;} right;
    int functionKeys[10];
    int backspace;
    int tab;
    int capsLock;
    int meta;
    struct {int scrollLock,capsLock,numLock;} locks;
    struct {int up,down,left,right} arrows;
} SpecialKeys;


typedef struct {
  int keyboard_irq_handled;
  unsigned char keyboard_buffer_pointer;
  unsigned char * keyboard_buffer;
  unsigned char lc;
  unsigned char scancode;
  unsigned char code;
  SpecialKeys *specialKeys;

  unsigned char (*keyboard_read_scan_code)(void);
  unsigned char (*keyboard_scan_code_to_ascii)(unsigned char scan_code);
  void (*keyboard)(Registers *regs);
  void (*Constructor)();

} KeyboardDriver;

#define KEYBOARD_DATA_PORT 0x60
#define BUFFER_MAX 100000

