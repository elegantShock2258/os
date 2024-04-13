#pragma once

#include "keyboard.c"
#include "printf.c"

unsigned char getc() {
  while (!keyboard_irq_handled)
    asm("nop");
  keyboard_irq_handled = 0;

  return keyboard_buffer[(BUFFER_MAX + keyboard_buffer_pointer - 1)%BUFFER_MAX];
}

unsigned int gets(char *buffer, unsigned int len) {
  unsigned int i = 0;
  while (i < len - 1 && getc() != '\n' && getc() != '\r') {
    buffer[i] = getc();
    i++;
  }
  buffer[i] = '\0';
  return i;
}