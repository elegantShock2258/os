#pragma once
#include "../../io/printf.h"
#include "../../utils/types.h"
#include "IDT.c"
#include "isrs_gen.c"

typedef struct {
  // in the reverse order they are pushed:
  u32 ds;                                         // data segment pushed by us
  u32 edi, esi, ebp, useless, ebx, edx, ecx, eax; // pusha
  u32 interrupt,
      error; // we push interrupt, error is pushed automatically (or our dummy)
  u32 eip, cs, eflags, esp, ss; // pushed automatically by CPU
} __attribute__((packed)) Registers;

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