#pragma once
#include "isr.h"
#include "isrs_gen/isrs_gen.c"


[[noreturn]] void __attribute__((cdecl)) ISR_Handler(Registers *regs) {
  printf("Interrupt. %d \n",regs->interrupt);
  asm("cli;hlt");
  while (1)
    ;
}

void isr_init() {
  isrs_gen_init();
  for (int i = 0; i < 256; i++)
    IDT_EnableGate(i);

  IDT_DisableGate(0x80);
}