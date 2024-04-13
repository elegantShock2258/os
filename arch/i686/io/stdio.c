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

unsigned int gets(char *buffer, unsigned int len) {

  unsigned int i = 0;
  char c;
  for (i = 0; i < len - 1; i++) {
    char ip = getc();
    if (ip == '\r' || ip == '\n')
      break;
    buffer[i] = ip;
  }

  buffer[i] = '\0';
  return i;
}