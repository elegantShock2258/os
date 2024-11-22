#pragma once

#include "../arch/i686/hal/io/serial.c"
#include "../utils/kernel_utils.c"

void outputQemuSerial(u8 data) { outb(0x3F8, data); }

void assert(bool condition, char *message) {
  if (condition) {
    outputQemuSerial('1');
    outputQemuSerial('\n');
    for (u32 i = 0; message[i]; i++)
      outputQemuSerial(message[i]);
  } else {
    outputQemuSerial('0');
    outputQemuSerial('\n');
    outputQemuSerial('N');
    outputQemuSerial('O');
    outputQemuSerial('T');
    outputQemuSerial('\n');
    for (u32 i = 0; message[i]; i++)
      outputQemuSerial(message[i]);
  }
}
void killQemu() {
  outb(0x501, 9); // send random data to port other than 0
}