#pragma once

#include "../arch/i686/hal/io/printf.c"
#include "../arch/i686/hal/io/serial.c"
#include "../arch/i686/hal/interrupts/pit/pit.c"
#include "../arch/i686/hal/memory/kheap/kheap.c"
#include "../drivers/keyboard/keyboard.c"
#include "../utils/kernel_utils.c"
#define test

void outputQemuSerial(u8 data) { outb(0x3F8, data); }
void outputQemuMessage(char *f) {
  for (int i = 0; f[i]; i++) {
    outputQemuSerial(f[i]);
  }
}
char buffer[2048] = "";
void logf(char *str, ...) {
  va_list va;
  va_start(va, str);
  outputQemuMessage("|[LOG]: ");
  vsnprintf_(buffer, sizeof(buffer), str, va);
  outputQemuMessage(buffer);
  outputQemuMessage("|");
  sleep(80);
  va_end(va);
}
// only use this during irq handlers or drivers like keyboard mouse or vesa 
void logfInterrupt(char *str, ...) {
  va_list va;
  va_start(va, str);
  outputQemuMessage("|[LOG]: ");
  vsnprintf_(buffer, sizeof(buffer), str, va);
  outputQemuMessage(buffer);
  outputQemuMessage("|");
  // no delay cuz asm("hlt") fucks up iret
  va_end(va);
}
void cleanLogf(char *str, ...) {
  va_list va;
  va_start(va, str);
  vsnprintf_(buffer, sizeof(buffer), str, va);
  outputQemuMessage(buffer);
  va_end(va);
}
void logKeys(KeyboardDriverState* driver, int scancode, int code){
  outputQemuMessage("|[LOG]: [KEYBOARD]: ");
  cleanLogf("%d %d", scancode,code);

  outputQemuMessage("|");
}

void logfBitMap(){
  outputQemuMessage("|[LOG]: [KMALLOC]: ");
  logBitmap();
  outputQemuMessage("|");
}

void printFramebuffer(u32* fb, int h,int w, char* title){
  logf("[FB]: %s: %dx%d\n",title,h,w);
  for(int i = 0;i<h*w;i++){
    u8 a = fb[i] & (0x000000ff);
    u8 b = fb[i] & (0x0000ff00);
    u8 c = fb[i] & (0x00ff0000);
    u8 d = fb[i] & (0xff000000);

    outputQemuSerial(d);
    outputQemuSerial(c);
    outputQemuSerial(b);
    outputQemuSerial(a);
  }
}
void outputInt(u8 data) { outputQemuSerial(data); }
void outputMessage(char *msg) {
  for (int i = 0; msg[i]; i++)
    outputQemuSerial(msg[i]);
}

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
    outputQemuSerial(' ');
    for (u32 i = 0; message[i]; i++)
      outputQemuSerial(message[i]);
  }
}
void killQemu() {
  outb(0x501, 9); // send random data to port other than 0
}