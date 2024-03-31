#include "../../utils/types.h"
#pragma once
typedef struct 
{
    // in the reverse order they are pushed:
    u32 ds;                                            // data segment pushed by us
    u32 edi, esi, ebp, useless, ebx, edx, ecx, eax;    // pusha
    u32 interrupt, error;                              // we push interrupt, error is pushed automatically (or our dummy)
    u32 eip, cs, eflags, esp, ss;                      // pushed automatically by CPU
} __attribute__((packed)) Registers;


typedef void (*ISRHandler)(Registers* regs);

void i686_ISR_Initialize();
void i686_ISR_RegisterHandler(int interrupt, ISRHandler handler);