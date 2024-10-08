#pragma once
#include "../../../../utils/kernel_utils.h"

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* Divisor for different baud rates */
enum BaudRate { Baud_115200 = 1, Baud_57600, Baud_19200, Baud_9600 };
// enum BaudRate divisor =Baud_115200;

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

static inline void outb(u16 port, u8 val) {
  __asm__ volatile("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline u8 inb(u16 port) {
  u8 ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}
static inline void io_wait(void) { outb(0x80, 0); }

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
  /* Tell the serial port to first expect the highest 8 bits, then the lowest
   * 8 bits. This is done by sending 0x80 to the line command port
   */
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com) {
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   * data length of 8 bits, one stop bit, no parity bit, break control
   * disabled and DLAB disabled
   */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo_buffer(unsigned short com) {
  /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
   * Content: | lvl | bs | r | dma | clt | clr | e |
   * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
   */
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com) {
  /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
   * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
   * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1 | = 0x03
   */
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com) {
  /* 0x20 = 0010 0000 */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(char *buf, unsigned int len) {
  serial_configure_baud_rate(SERIAL_COM1_BASE, 3);
  serial_configure_line(SERIAL_COM1_BASE);

  unsigned int i;
  for (i = 0; i < len; i++) {
    while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE))
      ;

    outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
  }
}
void serial_write_byte(unsigned short port, char byteData) {
  outb(port, byteData);
}

void serial_configure(unsigned short port, unsigned short baudRate) {
  serial_configure_baud_rate(port, baudRate);
  serial_configure_line(port);
  serial_configure_fifo_buffer(port);
  serial_configure_modem(port);
}