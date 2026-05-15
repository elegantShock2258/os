# isr.c

## Description
Implementation of ISR handling. It maps interrupts to high-level C functions and prints standard CPU exception messages during kernel panics.

## Imports
- [[isr.h.md]]
- [[isrs_gen.c.md]]

## Variables
- `ISRHandler g_ISRHandlers[256]`
- `static const char *const g_Exceptions[]`

## Functions
- `void ISR_Handler(Registers *regs)`: Dispatches the exception or panics the kernel with a register dump.
- `void isr_init()`: Calls `isrs_gen_init` and enables IDT gates.
- `void ISR_RegisterHandler(int interrupt, ISRHandler handler)`
