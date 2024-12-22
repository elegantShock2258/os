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

char* to_string(int value, char* buffer, int base) {
    if (base < 2 || base > 36) {
        *buffer = '\0';  // Invalid base
        return buffer;
    }

    bool is_negative = false;
    if (value < 0 && base == 10) {  // Handle negative numbers only for base 10
        is_negative = true;
        value = -value;
    }

    int i = 0;

    // Process the number and convert to the given base
    do {
        int digit = value % base;
        buffer[i++] = (digit < 10) ? '0' + digit : 'a' + digit - 10;
        value /= base;
    } while (value != 0);

    if (is_negative) {
        buffer[i++] = '-';
    }

    // Null-terminate the string
    buffer[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; ++j, --k) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return buffer;
}
