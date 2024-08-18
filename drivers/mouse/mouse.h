#pragma once

#include "../../arch/i686/hal/interrupts/isr/isr.c"
#include "../../arch/i686/hal/io/serial.c"
#include "../../utils/kernel_utils.c"

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

typedef struct {
  int yOverflow : 1;
  int xOverflow : 1;
  int ySign : 1;
  int xSign : 1;
  int always1 : 1;
  int middle : 1;
  int right : 1;
  int left : 1;
} mouse_byte_state_data;

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

typedef struct {
    u8 mouse_cycle;
    mouse_device_packet_t packet;
    int mouse_x;
    int mouse_y;
    int8_t *mouse_byte;
    mouse_byte_state_data mb;
    
    void (*mouse_wait)(u8 a_type);
    void (*mouse_write)(u8 write);
    u8 (*mouse_read)();
    void (*mouse)(Registers *r);
    void (*mouse_install)();
    void (*Constructor)();
} MouseDriverState;


