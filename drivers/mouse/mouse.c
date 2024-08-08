#pragma once
#include "../../arch/i686/hal/interrupts/isr/isr.c"
#include "../../arch/i686/hal/io/serial.c"
#include "../../utils/kernel_utils.c"

u8 mouse_cycle = 0;
typedef enum {
  LEFT_CLICK = 0x01,
  RIGHT_CLICK = 0x02,
  MIDDLE_CLICK = 0x04
} mouse_click_t;

typedef struct {
  uint32_t magic;
  int8_t x_difference;
  int8_t y_difference;
  mouse_click_t buttons;
} mouse_device_packet_t;

#define MOUSE_MAGIC 0xFEED1234
#define PACKETS_IN_PIPE 1024
#define DISCARD_POINT 32

#define MOUSE_IRQ 12

#define MOUSE_PORT 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT 0x02
#define MOUSE_BBIT 0x01
#define MOUSE_WRITE 0xD4
#define MOUSE_F_BIT 0x20
#define MOUSE_V_BIT 0x08

mouse_device_packet_t packet;
int8_t mouse_byte[3];
int mouse_x = 0, mouse_y = 0;
;

void mouse_wait(u8 a_type) {
  uint32_t timeout = 100000;
  if (!a_type) {
    while (--timeout) {
      if ((inb(MOUSE_STATUS) & MOUSE_BBIT) == 1) {
        return;
      }
    }
    return;
  } else {
    while (--timeout) {
      if (!((inb(MOUSE_STATUS) & MOUSE_ABIT))) {
        return;
      }
    }
    return;
  }
}

void mouse_write(u8 write) {
  mouse_wait(1);
  outb(MOUSE_STATUS, MOUSE_WRITE);
  mouse_wait(1);
  outb(MOUSE_PORT, write);
}

u8 mouse_read() {
  mouse_wait(0);
  char t = inb(MOUSE_PORT);
  return t;
}

void mouse(Registers *r) {
  u8 status = inb(MOUSE_STATUS);
  while (status & MOUSE_BBIT) {
    int8_t mouse_in = inb(MOUSE_PORT);
    if (status & MOUSE_F_BIT) {
      switch (mouse_cycle) {
      case 0:
        mouse_byte[0] = mouse_in;
        if (!(mouse_in & MOUSE_V_BIT))
          return;
        ++mouse_cycle;
        break;
      case 1:
        mouse_byte[1] = mouse_in;
        ++mouse_cycle;
        break;
      case 2:
        mouse_byte[2] = mouse_in;
        /* We now have a full mouse packet ready to use */
        if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40) {
          /* x/y overflow? bad packet! */
          break;
        }
        packet.magic = MOUSE_MAGIC;
        packet.x_difference = mouse_byte[1];
        packet.y_difference = mouse_byte[2];
        mouse_x += mouse_byte[1];
        mouse_y += mouse_byte[2];
        packet.buttons = 0;
        if (mouse_byte[0] & 0x01) {
          packet.buttons |= LEFT_CLICK;
        }
        if (mouse_byte[0] & 0x02) {
          packet.buttons |= RIGHT_CLICK;
        }
        if (mouse_byte[0] & 0x04) {
          packet.buttons |= MIDDLE_CLICK;
        }
        mouse_cycle = 0;

        break;
      }
    }
    status = inb(MOUSE_STATUS);
  }
}

void mouse_install() {
  u8 status;
  mouse_wait(1);
  outb(MOUSE_STATUS, 0xA8);
  mouse_wait(1);
  outb(MOUSE_STATUS, 0x20);
  mouse_wait(0);
  status = inb(0x60) | 2;
  mouse_wait(1);
  outb(MOUSE_STATUS, 0x60);
  mouse_wait(1);
  outb(MOUSE_PORT, status);
  mouse_write(0xF6);
  mouse_read();
  mouse_write(0xF4);
  mouse_read();
}