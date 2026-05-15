# serial.c

## Description
Driver for serial port (COM1) communication, primarily used for debugging output to the emulator or host.

## Imports
- [[kernel_utils.h.md]]

## Functions
- `void outb(u16 port, u8 val)`, `u8 inb(u16 port)`, `void io_wait(void)`
- `void serial_configure_baud_rate(unsigned short com, unsigned short divisor)`
- `void serial_configure_line(...)`, `serial_configure_fifo_buffer(...)`, `serial_configure_modem(...)`
- `int serial_is_transmit_fifo_empty(...)`
- `void serial_write(...)`, `void serial_write_byte(...)`
