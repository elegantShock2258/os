#pragma once

#include "keyboard.c"
#include "printf.c"

unsigned char getc() {
  while (!keyboard_irq_handled)
    asm("nop");
  keyboard_irq_handled = 0;
  return keyboard_buffer[(BUFFER_MAX + keyboard_buffer_pointer - 1) %
                         BUFFER_MAX];
}
