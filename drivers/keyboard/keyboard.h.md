# keyboard.h

## Description
Header definitions for the PS/2 keyboard driver. It tracks key states including special and extended keys using a large `SpecialKeys` structure.

## Imports
- [[irq.c.md]]
- [[isr.h.md]]
- [[printf.c.md]]
- [[serial.c.md]]
- [[buffer.c.md]]

## Types
- `SpecialKeys`: Huge struct keeping track of modifiers, arrows, multimedia keys, etc.
- `KeyboardDriverState`: Object structure managing the circular buffer of keypresses and function pointers to handler methods.
