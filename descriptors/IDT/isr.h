#pragma once
#include "../../utils/kernel_utils.h"
#include "IDT.h"
typedef struct {
  // in the reverse order they are pushed:
  u32 ds;                                         // data segment pushed by us
  u32 edi, esi, ebp, useless, ebx, edx, ecx, eax; // pusha
  u32 interrupt,
      error; // we push interrupt, error is pushed automatically (or our dummy)
  u32 eip, cs, eflags, esp, ss; // pushed automatically by CPU
} __attribute__((packed)) Registers;

[[noreturn]] void __attribute__((cdecl)) ISR_Handler(Registers *regs);

void isr_init();