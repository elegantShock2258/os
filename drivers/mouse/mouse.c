#pragma once
#include "mouse.h"

u8 _Mouse_cycle = 0;

mouse_device_packet_t _Mouse_packet;
int8_t _Mouse_byte[3];
int _Mouse_x = 0, _Mouse_y = 0;
mouse_byte_state_data _Mouse_mb;

MouseDriverState  MouseDriver;

void _Mouse_wait(u8 a_type) {
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

void _Mouse_write(u8 write) {
  _Mouse_wait(1);
  outb(MOUSE_STATUS, MOUSE_WRITE);
  _Mouse_wait(1);
  outb(MOUSE_PORT, write);
}

u8 _Mouse_read() {
  _Mouse_wait(0);
  char t = inb(MOUSE_PORT);
  return t;
}

void _Mouse(Registers *r) {
  u8 status = inb(MOUSE_STATUS);
  while (status & MOUSE_BBIT) {
    int8_t mouse_in = inb(MOUSE_PORT);
    if (status & MOUSE_F_BIT) {
      switch (MouseDriver.mouse_cycle) {
      case 0:
        MouseDriver.mouse_byte[0] = mouse_in;
        if (!(mouse_in & MOUSE_V_BIT))
          return;
        ++MouseDriver.mouse_cycle;
        break;
      case 1:
        MouseDriver.mouse_byte[1] = mouse_in;
        ++MouseDriver.mouse_cycle;
        break;
      case 2:
        MouseDriver.mouse_byte[2] = mouse_in;
        /* We now have a full mouse packet ready to use */
        if (MouseDriver.mouse_byte[0] & 0x80 || MouseDriver.mouse_byte[0] & 0x40) {
          /* x/y overflow? bad packet! */
          break;
        }
        MouseDriver.packet.magic = MOUSE_MAGIC;
        MouseDriver.packet.x_difference = MouseDriver.mouse_byte[1];
        MouseDriver.packet.y_difference = MouseDriver.mouse_byte[2];
        MouseDriver.packet.buttons = 0;
        MouseDriver.mb = *(mouse_byte_state_data *)&MouseDriver.mouse_byte[0];

        MouseDriver.mouse_x += (MouseDriver.mb.xSign ? 1 : -1) * MouseDriver.mouse_byte[1];
        MouseDriver.mouse_y += (MouseDriver.mb.ySign ? 1 : -1) * MouseDriver.mouse_byte[2];
        // checking coords
        // Clamp mouse_x to screen width
        if (MouseDriver.mouse_x < 0) {
          MouseDriver.mouse_x = 0;
        } else if (MouseDriver.mouse_x >= 1920) {
          MouseDriver.mouse_x = 1920 - 1; // Keep it within bounds
        }

        // Clamp mouse_y to screen height
        if (MouseDriver.mouse_y < 0) {
          MouseDriver.mouse_y = 0;
        } else if (MouseDriver.mouse_y >= 1080) {
          MouseDriver.mouse_y = 1080 - 1; // Keep it within bounds
        }
        if (MouseDriver.mouse_byte[0] & 0x01) {
          MouseDriver.packet.buttons |= LEFT_CLICK;
        }
        if (MouseDriver.mouse_byte[0] & 0x02) {
          MouseDriver.packet.buttons |= RIGHT_CLICK;
        }
        if (MouseDriver.mouse_byte[0] & 0x04) {
          MouseDriver.packet.buttons |= MIDDLE_CLICK;
        }
        MouseDriver.mouse_cycle = 0;
        break;
      }
    }
    status = inb(MOUSE_STATUS);
  }

  // EvalMouse();
}

void _Mouse_install() {
  u8 status;
  _Mouse_wait(1);
  outb(MOUSE_STATUS, 0xA8);
  _Mouse_wait(1);
  outb(MOUSE_STATUS, 0x20);
  _Mouse_wait(0);
  status = inb(0x60) | 2;
  _Mouse_wait(1);
  outb(MOUSE_STATUS, 0x60);
  _Mouse_wait(1);
  outb(MOUSE_PORT, status);
  _Mouse_write(0xF6);
  _Mouse_read();
  _Mouse_write(0xF4);
  _Mouse_read();
}

void MouseConstructor() {

  MouseDriver.mouse_cycle = _Mouse_cycle;
  MouseDriver.packet = _Mouse_packet;
  MouseDriver.mouse_x = _Mouse_x;
  MouseDriver.mouse_y = _Mouse_y;
  MouseDriver.mouse_byte = _Mouse_byte;
  MouseDriver.mb = _Mouse_mb;

  MouseDriver.mouse_wait = _Mouse_wait;
  MouseDriver.mouse_write = _Mouse_write;
  MouseDriver.mouse_read = _Mouse_read;
  MouseDriver.mouse = _Mouse;
  MouseDriver.mouse_install = _Mouse_install;
  MouseDriver.Constructor = MouseConstructor;

  _Mouse_install();
  IRQ_RegisterHandler(12, _Mouse);
}
