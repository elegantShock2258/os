#pragma once

#include "../../../../drivers/keyboard/keyboard.c"
#include "printf.c"

unsigned char getc() {
  while (!KeyboardDriverState->keyboard_irq_handled)
    asm("nop");
  KeyboardDriverState->keyboard_irq_handled = 0;

  return KeyboardDriverState->keyboard_buffer[(BUFFER_MAX + KeyboardDriverState->keyboard_buffer_pointer - 1) %
                         BUFFER_MAX];
}

unsigned int gets(char *buffer, unsigned int len) {

  unsigned int i = 0;
  char c;
  for (i = 0; i < len - 1; i++) {
    char ip = getc();
    if (ip == '\r' || ip == '\n')
      break;
    // printf("%c", ip); print for visiblity
    buffer[i] = ip;
  }

  buffer[i] = '\0';
  return i;
}