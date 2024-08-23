#pragma once

#include "../../../../drivers/keyboard/keyboard.c"
#include "printf.c"

unsigned char getc() {
  while (!KeyboardDriver.keyboard_irq_handled)
    asm("nop");
  KeyboardDriver.keyboard_irq_handled = 0;
  char t = KeyboardDriver.keyboard_buffer.top(&KeyboardDriver.keyboard_buffer);
  printf("GETC: %c\n", t);
  return t;
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