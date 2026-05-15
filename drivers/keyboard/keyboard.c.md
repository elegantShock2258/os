# keyboard.c

## Description
Implementation of the PS/2 Keyboard driver. Includes a US keyboard scancode to ASCII map, special key tracker, and an IRQ1 handler.

## Imports
- [[keyboard.h.md]]
- [[vbe.c.md]]
- [[testing.c.md]]

## Variables
- `KeyboardDriverState KeyboardDriver`
- `CircularBuffer _Keyoard_CircularBuffer`

## Functions
- `static void _Keyboard_update_special_keys(...)`
- `unsigned char _Keyboard_read_scan_code(void)`
- `unsigned char _Keyboard_scan_code_to_ascii(unsigned char scan_code)`
- `unsigned char _Keyboard_get_char()`
- `void _Keyboard(Registers *regs)`: ISR callback invoked upon IRQ1. Processes scancodes and places them in the buffer.
- `void KeyboardConstructor()`: Initializes the `KeyboardDriver` state and registers the IRQ1 handler.
