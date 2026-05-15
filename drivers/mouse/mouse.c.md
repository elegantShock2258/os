# mouse.c

## Description
Implementation of the PS/2 Mouse driver. Handles the 3-byte cyclic packet protocol, updates internal X/Y coordinates based on relative movement, and clamps cursor coordinates to 1920x1080 bounds.

## Imports
- [[mouse.h.md]]

## Variables
- `MouseDriverState MouseDriver`

## Functions
- `void _Mouse_wait(u8 a_type)`: Busy-waits until the mouse controller is ready for read or write.
- `void _Mouse_write(u8 write)`
- `u8 _Mouse_read()`
- `void _Mouse(Registers *r)`: The main ISR for IRQ12. Reads bytes, accumulates them into a 3-byte cycle, and parses the relative X/Y movement and button states.
- `void _Mouse_install()`: Sends configuration commands to the keyboard/mouse controller to enable the aux port and packet streaming.
- `void MouseConstructor()`: Wires up the driver interface and registers the IRQ.
